#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include <ctime>

using namespace std;

class frame
{
  public:
    string data;
    int seq;
};

class Simulator
{
    queue<frame> channel;
    queue<frame> resendChannel;
    frame* frames;
    queue<int> acks;
    int totalFrames;
    int windowSize;
    int i;
    bool isNoisy;

  public:
    Simulator();
    ~Simulator();
    void sender(int);
    void reciever();
    void recieveACK();
    void simulate(bool isNoisy=false);
};

int main()
{
    Simulator sim;
    sim.simulate();
}

Simulator::Simulator()
{
    cout<<"Enter total number of frames to simulate: ";
    cin>>totalFrames;
    cout<<"Enter window size: ";
    cin>>windowSize;
    frames = new frame[totalFrames];
    for(int i=0;i<totalFrames;i++)
    {
        cout<<"Enter frame number "<<i<<" : ";
        cin>>frames[i].data;
        frames[i].seq = i%windowSize;
    }
    isNoisy = false;
}   

Simulator::~Simulator()
{
    if(frames!=NULL)
        delete[] frames;
}

void Simulator::sender(int from)
{
    for(int i=from;i<from+windowSize&&i<totalFrames;i++)
    {
        cout<<"SENDER: sent frame "<<frames[i].data<<" SEQ: "<<frames[i].seq<<endl;
        channel.push(frames[i]);
        acks.push(frames[i].seq);
    }
}

void Simulator::reciever()
{
    while(!channel.empty())
    {
        cout<<"RECIEVER: Recieved Frame: "<<channel.front().data<<" SEQ: "<<channel.front().seq<<"; sending ACK"<<endl;
        channel.pop();
    }
}

void Simulator::recieveACK()
{
    while(!acks.empty())
    {
        cout<<"SENDER: Recived ACK for seq: "<<acks.front()<<endl;
        acks.pop();
        i++;
    }
}

void Simulator::simulate(bool isNoisy)
{
    for(i=0;i<totalFrames;)
    {
        sender(i);
        reciever();
        recieveACK();
    }
}