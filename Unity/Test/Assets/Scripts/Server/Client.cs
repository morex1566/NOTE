using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using UnityEngine.UI;
using UnityEngine;
using System;
using TMPro;

public class Client : MonoBehaviour
{
    public GameObject chatContainer;
    public GameObject message;
    public string clientName;

    private bool isSocketReady;
    private TcpClient socket;
    private NetworkStream stream;
    private StreamWriter writer;
    private StreamReader reader;

    private string host;
    private int port;

    public void ConnectToServer()
    {
        // 만약 이미 연결되어있다면, 이 함수를 무시합니다.
        if (isSocketReady)
        {
            return;
        }

        // 기본 호스트 / 포트 값
        string defaultHost = "192.168.219.103";
        int defaultPort = 6321;


        // 입력된 호스트 / 포트 값
        string inputHost = GameObject.Find("HostInput").GetComponent<TMP_InputField>().text;
        int inputPort;
        int.TryParse(GameObject.Find("PortInput").GetComponent<TMP_InputField>().text, out inputPort);

        host = inputHost != "" ? inputHost : defaultHost;
        port = inputPort != 0 ? inputPort : defaultPort;

        // 소켓 생성
        try
        {
            socket = new TcpClient(host, port);
            stream = socket.GetStream();
            writer = new StreamWriter(stream);
            reader = new StreamReader(stream);
            isSocketReady = true;
        }
        catch (Exception e)
        {
            Debug.Log("Socket error : " + e.Message);
        }
    }

    private void Update()
    {
        if (isSocketReady)
        {
            if (stream.DataAvailable)
            {
                string data = reader.ReadLine();
                if (data != null)
                {
                    ReadData(data);
                }
            }
        }

    }

    private void ReadData(string data)
    {
        GameObject messageObj = Instantiate(message, chatContainer.transform);

        messageObj.GetComponentInChildren<TMP_Text>().text = data;
    }

    private void Send(string data)
    {
        if (!isSocketReady)
        {
            return;
        }

        writer.WriteLine(data);
        writer.Flush();
    }

    public void OnSendButtonDown()
    {
        string message = GameObject.Find("SendInput").GetComponent<TMP_InputField>().text;
        Send(message);
    }
}
