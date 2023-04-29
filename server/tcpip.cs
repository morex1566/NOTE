using System.Net;
using System.Net.Sockets;

namespace Server;

public class CNetworkService
{
    // INFO : listener
    private CListener client_listener;
    
    // INFO : sender, receiver
    private SocketAsyncEventArgsPool receive_event_args_pool;
    private SocketAsyncEventArgsPool send_event_args_pool;
    
    // INFO : packet manager
    private bufferManager buffer_manager;
    
    // INFO : connection callback
    public delegate void SessionHandler(CUserToken token);
    public SessionHandler session_create_callback { get; set; }

    public CNetworkService()
    {
        receive_event_args_pool = new SocketAsyncEventArgsPool(max_connections);
        send_event_args_pool = new SocketAsyncEventArgsPool(max_connections);

        // init
        for (int i = 0; i < this.max_connections; i++)  
        {  
            CUserToken token = new CUserToken();  
  
            // receive pool  
            {  
                //Pre-allocate a set of reusable SocketAsyncEventArgs  
                arg = new SocketAsyncEventArgs();  
                arg.Completed += new EventHandler<SocketAsyncEventArgs>(receive_completed);  
                arg.UserToken = token;

                buffer_manager.SetBuffer(arg);
  
                // add SocketAsyncEventArg to the pool  
                this.receive_event_args_pool.Push(arg);  
            }

            // send pool  
            {  
                //Pre-allocate a set of reusable SocketAsyncEventArgs  
                arg = new SocketAsyncEventArgs();  
                arg.Completed += new EventHandler<SocketAsyncEventArgs>(send_completed);  
                arg.UserToken = token;  
                
                buffer_manager.SetBuffer(arg);

                // add SocketAsyncEventArg to the pool  
                this.send_event_args_pool.Push(arg);  
            }  
        }

        buffer_manager = new bufferManager(max_connections * buffer_size * pre_alloc_count, buffer_size);
    }
    
    // INFO : listen
    public void listen(string host, int port, int backlog)
    {
        CListener listener = new CListener();
        
        // set callback function if client was access
        listener.callback_on_newclient += on_new_client;
        
        // start to wait access from client
        listener.start(host, port, backlog);
    }

    private void on_new_client(Socket client_socket, object token)
    {
        // get event handler from pool
        SocketAsyncEventArgs receive_args = receive_event_args_pool.Pop();
        SocketAsyncEventArgs send_args = receive_event_args_pool.Pop();
        
        // give token to client
        CUserToken user_token = receive_args.UserToken as CUserToken;
        session_create_callback(user_token);
        
        // ready to talk with client
        begin_receive(client_socket, receive_args, send_args);
    }

    private void begin_receive(Socket socket, SocketAsyncEventArgs receive_args, SocketAsyncEventArgs send_args)
    {
        // store info at token
        CUserToken token = receive_args.UserToken as CUserToken;
        token.set_event_args(receive_args, send_args);
        token.socket = socket;

        // processing argument event
        bool pending = socket.ReceiveAsync(receive_args);
        if (!pending)
        {
            process_receive(receive_args);
        }
    }

    
    private void receive_completed(object sender, SocketAsyncEventArgs e)
    {
        if (e.LastOperation == SocketAsyncOperation.Receive)
        {
            process_receive(e);
            return;
        }
        
        throw new ArgumentException("The last operation completed on the socket was not a receive.");  
    }

    // INFO : work client msg
    private void process_receive(SocketAsyncEventArgs e)
    {
        CUserToken token = e.UserToken as CUserToken;
        if (e.BytesTransferred > 0 && e.SocketError == SocketError.Success)
        {
            // client request (data, buffer position, data size)
            token.on_receive(e.Buffer, e.Offset, e.BytesTransferred);
            
            // set receive mode
            bool pending = token.socket.ReceiveAsync(e);  
            if (!pending)  
            {  
                process_receive(e);  
            }  
        }  
        else  
        {  
            Console.WriteLine(string.Format("error {0},  transferred {1}", e.SocketError, e.BytesTransferred));  
            close_clientsocket(token);  
        } 
    }
    
    // INFO : create packet from client msg
    private void on_receive(byte[] buffer, int offset, int transfered)
    {
        // 추후에 다른 방식으로 packet을 해석할 수 있으니 다시 메소드 처리
        message_resolver.on_receive(buffer, offset, transfered, on_message);
    }
}

public class Defines
{
    public static readonly short HEADERSIZE = 2;
}

public class CMessageResolver
{
    public delegate void CompletedMessageCallback(Const<byte[]> buffer);

    private int message_size;
    private byte[] message_buffer = new byte[1024];

    private int current_position;
    private int position_to_read;
    private int remain_bytes;

    public CMessageResolver()
    {
        message_size = 0;
        current_position = 0;
        position_to_read = 0;
        remain_bytes = 0;
    }
    
    bool read_until(byte[] buffer, ref int src_position, int offset, int transffered)  
    {  
        if (this.current_position >= offset + transffered)  
        {  
            // 들어온 데이터 만큼 다 읽은 상태이므로 더이상 읽을 데이터가 없다.  
            return false;  
        }  
  
        // 읽어와야 할 바이트.  
        // 데이터가 분리되어 올 경우 이전에 읽어놓은 값을 빼줘서 부족한 만큼 읽어올 수 있도록 계산해 준다.  
        int copy_size = this.position_to_read - this.current_position;  
  
        // 앗! 남은 데이터가 더 적다면 가능한 만큼만 복사한다.  
        if (this.remain_bytes < copy_size)  
        {  
            copy_size = this.remain_bytes;  
        }  
  
        // 버퍼에 복사.  
        Array.Copy(buffer, src_position, this.message_buffer, this.current_position, copy_size);  
  
  
        // 원본 버퍼 포지션 이동.  
        src_position += copy_size;  
  
        // 타겟 버퍼 포지션도 이동.  
        this.current_position += copy_size;  
  
        // 남은 바이트 수.  
        this.remain_bytes -= copy_size;  
  
        // 목표지점에 도달 못했으면 false  
        if (this.current_position < this.position_to_read)  
        {  
            return false;  
        }  
  
        return true;  
    }  
  
    /// <summary>  
    /// 소켓 버퍼로부터 데이터를 수신할 때 마다 호출된다.  
    /// 데이터가 남아 있을 때 까지 계속 패킷을 만들어 callback을 호출 해 준다.  
    /// 하나의 패킷을 완성하지 못했다면 버퍼에 보관해 놓은 뒤 다음 수신을 기다린다.  
    /// </summary>  
    /// <param name="buffer"></param>  
    /// <param name="offset"></param>  
    /// <param name="transffered"></param>  
    public void on_receive(byte[] buffer, int offset, int transffered, CompletedMessageCallback callback)  
    {  
        // 이번 receive로 읽어오게 될 바이트 수.  
        this.remain_bytes = transffered;  
  
        // 원본 버퍼의 포지션값.  
        // 패킷이 여러개 뭉쳐 올 경우 원본 버퍼의 포지션은 계속 앞으로 가야 하는데 그 처리를 위한 변수이다.  
        int src_position = offset;  
  
        // 남은 데이터가 있다면 계속 반복한다.  
        while (this.remain_bytes > 0)  
        {  
            bool completed = false;  
  
            // 헤더만큼 못읽은 경우 헤더를 먼저 읽는다.  
            if (this.current_position < Defines.HEADERSIZE)  
            {  
                // 목표 지점 설정(헤더 위치까지 도달하도록 설정).  
                this.position_to_read = Defines.HEADERSIZE;  
  
                completed = read_until(buffer, ref src_position, offset, transffered);  
                if (!completed)  
                {  
                    // 아직 다 못읽었으므로 다음 receive를 기다린다.  
                    return;  
                }  
  
                // 헤더 하나를 온전히 읽어왔으므로 메시지 사이즈를 구한다.  
                this.message_size = get_body_size();  
  
                // 다음 목표 지점(헤더 + 메시지 사이즈).  
                this.position_to_read = this.message_size + Defines.HEADERSIZE;  
            }  
  
            // 메시지를 읽는다.  
            completed = read_until(buffer, ref src_position, offset, transffered);  
  
            if (completed)  
            {  
                // 패킷 하나를 완성 했다.  
                callback(new Const<byte[]>(this.message_buffer));  
  
                clear_buffer();  
            }  
        }  
    }  
  
    int get_body_size()  
    {  
        // 헤더에서 메시지 사이즈를 구한다.  
        // 헤더 타입은 Int16, Int32두가지가 올 수 있으므로 각각을 구분하여 처리한다.  
        // 사실 헤더가 바뀔 경우는 없을테니 그냥 한가지로 고정하는편이 깔끔할것 같다.  
  
        Type type = Defines.HEADERSIZE.GetType();  
        if (type.Equals(typeof(Int16)))  
        {  
            return BitConverter.ToInt16(this.message_buffer, 0);  
        }  
  
        return BitConverter.ToInt32(this.message_buffer, 0);  
    }  
  
    void clear_buffer()  
    {  
        Array.Clear(this.message_buffer, 0, this.message_buffer.Length);  
  
        this.current_position = 0;  
        this.message_size = 0;  
    }  
}  
public class CUserToken
{
}

// INFO : MSDN pooling object
class SocketAsyncEventArgsPool  
{  
    Stack<SocketAsyncEventArgs> m_pool;  
  
    // Initializes the object pool to the specified size  
    //  
    // The "capacity" parameter is the maximum number of   
    // SocketAsyncEventArgs objects the pool can hold  
    public SocketAsyncEventArgsPool(int capacity)  
    {  
        m_pool = new Stack<SocketAsyncEventArgs>(capacity);  
    }  
  
    // Add a SocketAsyncEventArg instance to the pool  
    //  
    //The "item" parameter is the SocketAsyncEventArgs instance   
    // to add to the pool  
    public void Push(SocketAsyncEventArgs item)  
    {  
        if (item == null) { throw new ArgumentNullException("Items added to a SocketAsyncEventArgsPool cannot be null"); }  
        lock (m_pool)  
        {  
            m_pool.Push(item);  
        }  
    }  
  
    // Removes a SocketAsyncEventArgs instance from the pool  
    // and returns the object removed from the pool  
    public SocketAsyncEventArgs Pop()  
    {  
        lock (m_pool)  
        {  
            return m_pool.Pop();  
        }  
    }  
  
    // The number of SocketAsyncEventArgs instances in the pool  
    public int Count  
    {  
        get { return m_pool.Count; }  
    }  
}  

public class BufferManager  
{  
  
    int m_numBytes;                 // the total number of bytes controlled by the buffer pool  
    byte[] m_buffer;                // the underlying byte array maintained by the Buffer Manager  
    Stack<int> m_freeIndexPool;     //   
    int m_currentIndex;  
    int m_bufferSize;  
  
    public BufferManager(int totalBytes, int bufferSize)  
    {  
        m_numBytes = totalBytes;  
        m_currentIndex = 0;  
        m_bufferSize = bufferSize;  
        m_freeIndexPool = new Stack<int>();  
    }  
  
    /// <summary>  
    /// Allocates buffer space used by the buffer pool  
    /// </summary>  
    public void InitBuffer()  
    {  
        // create one big large buffer and divide that out to each SocketAsyncEventArg object  
        m_buffer = new byte[m_numBytes];  
    }  
  
    /// <summary>  
    /// Assigns a buffer from the buffer pool to the specified SocketAsyncEventArgs object  
    /// </summary>  
    /// <returns>true if the buffer was successfully set, else false</returns>  
    public bool SetBuffer(SocketAsyncEventArgs args)  
    {  
        if (m_freeIndexPool.Count > 0)  
        {  
            args.SetBuffer(m_buffer, m_freeIndexPool.Pop(), m_bufferSize);  
        }  
        else  
        {  
            if ((m_numBytes - m_bufferSize) < m_currentIndex)  
            {  
                return false;  
            }  
            args.SetBuffer(m_buffer, m_currentIndex, m_bufferSize);  
            m_currentIndex += m_bufferSize;  
        }  
        return true;  
    }  
  
    /// <summary>  
    /// Removes the buffer from a SocketAsyncEventArg object.  This frees the buffer back to the   
    /// buffer pool  
    /// </summary>  
    public void FreeBuffer(SocketAsyncEventArgs args)  
    {  
        m_freeIndexPool.Push(args.Offset);  
        args.SetBuffer(null, 0, 0);  
    }  
}  

public class CListener
{
    // INFO : async accept event
    private SocketAsyncEventArgs accept_args;
    
    // INFO : listen socket
    private Socket listen_socket;
    
    // INFO : flow controller
    private AutoResetEvent flow_control_event;
    
    // INFO : new client connection callback
    public delegate void NewclientHandler(Socket client_socket, object token);
    public NewclientHandler? callback_on_newclient;


    public void start(string host, int port, int backlog)
    {
        // create socket
        listen_socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

        IPAddress address;
        if (host == "0.0.0.0")
        {
            address = IPAddress.Any;
        }
        else
        {
            address = IPAddress.Parse(host);
        }

        IPEndPoint endpoint = new IPEndPoint(address, port);

        try
        {
            listen_socket.Bind(endpoint);
            listen_socket.Listen(backlog);

            accept_args = new SocketAsyncEventArgs();
            accept_args.Completed += new EventHandler<SocketAsyncEventArgs>(on_accept_completed);

            // none async work
            // listen_socket.AcceptAsync(accept_args);
            // async work
            Thread listen_thread = new Thread(do_listen);
            listen_thread.Start();
        }
        catch (Exception exception)
        {
            Console.WriteLine(exception);
            throw;
        }
        
    }
    

    private void do_listen()
    {
        flow_control_event = new AutoResetEvent(false);

        while (true)
        {
            accept_args.AcceptSocket = null;

            bool pending = false;
            try
            {
                pending = listen_socket.AcceptAsync(accept_args);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

            // INFO : check accepted client
            if (!pending)
            {
                on_accept_completed(null, accept_args);
            }
            
            flow_control_event.WaitOne();
        }
    }

    private void on_accept_completed(object? sender, SocketAsyncEventArgs e)
    {
        if (e.SocketError == SocketError.Success)
        {
            Socket client_socket = e.AcceptSocket;
            
            if (e.UserToken != null) callback_on_newclient?.Invoke(client_socket, e.UserToken);

            return;
        }
        else
        {
            Console.WriteLine("Failed to accept client.");
        }
        
        // start to accept next socket
        flow_control_event.Set();
    }
}