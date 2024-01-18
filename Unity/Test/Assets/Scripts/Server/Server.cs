using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net;
using System.Net.Sockets;
using TMPro;
using UnityEditor;
using UnityEngine;

public class Server : MonoBehaviour
{
    public GameObject chatContainer;
    public GameObject message;

    public IPAddress ip = IPAddress.Parse("192.168.219.103");
    public int port = 6321;
    private List<ServerClient> clients;
    private List<ServerClient> disconnectList;
    private TcpListener server;
    private bool isServerStarted;

    private void Start()
    {
        clients = new List<ServerClient>();
        disconnectList = new List<ServerClient>();

        try
        {
            server = new TcpListener(ip, port);
            server.Start();
            StartListening();
            isServerStarted = true;
            Debug.Log("Server has benn started on port : " + port);
        }
        catch (Exception e)
        {
            Debug.Log("Socket error : " + e.Message);
        }
    }

    private void Update()
    {
        if (!isServerStarted)
        {
            return;
        }

        foreach (ServerClient client in clients)
        {
            // 클라이언트가 연결X, 제거해주세요.
            if (!IsConnected(client.Client))
            {
                client.Client.Close();
                disconnectList.Add(client);
                continue;
            }
            // 클라이언트가 연결O, 클라이언트의 메세지를 확인해주세요.
            else
            {
                NetworkStream stream = client.Client.GetStream();
                if (stream.DataAvailable)
                {
                    StreamReader reader = new StreamReader(stream, true);
                    string data = reader.ReadLine();

                    if (data != null)
                    {
                        ReadData(client, data);
                    }
                }
            }
        }
    }

    private void StartListening()
    {
        server.BeginAcceptTcpClient(AcceptTcpClient, server);
    }

    private bool IsConnected(TcpClient tcpClient)
    {
        try
        {
            if (tcpClient != null && tcpClient.Client != null && tcpClient.Client.Connected)
            {
                if (tcpClient.Client.Poll(0, SelectMode.SelectRead))
                {
                    return !(tcpClient.Client.Receive(new byte[1], SocketFlags.Peek) == 0);
                }

                return true;
            }
            else
            {
                return false;
            }
        }
        catch
        {
            return false;
        }
    }

    private void AcceptTcpClient(IAsyncResult asyncResult)
    {
        TcpListener listener = (TcpListener)asyncResult.AsyncState;

        clients.Add(new ServerClient(listener.EndAcceptTcpClient(asyncResult)));
        StartListening();
        Broadcast(clients[clients.Count - 1].ClientName + " has connected!", clients);
    }

    private void Broadcast(string data, List<ServerClient> clients)
    {
        foreach (ServerClient client in clients)
        {
            try
            {
                StreamWriter writer = new StreamWriter(client.Client.GetStream());
                writer.WriteLine(data);
                writer.Flush();
            }
            catch (Exception e)
            {
                Debug.Log("Write error : " + e.Message + " to client " + client.ClientName);
            }
        }
    }

    private void ReadData(ServerClient client, string data)
    {
        Broadcast(client.ClientName + " : " + data, clients);
    }
}

public class ServerClient
{
    public TcpClient Client;
    public string ClientName;

    public ServerClient(TcpClient client)
    {
        Client = client;
        ClientName = "Guest";
    }
}