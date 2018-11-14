#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <queue>
#include <string>

using namespace std;

class frame
{
  public:
    string data;
    int seq;
    int ack;
    bool isResent;
};

class Simulator
{
    queue<frame> channel;
    frame *frames;
    int totalFrames;
    int windowSize;

  public:
    Simulator();
    ~Simulator();
    void sender(int from);
    void reciever();
    void recieveACK();
    void simulate();
};

int main()
{
    Simulator sim;
    sim.simulate();
}

Simulator::Simulator()
{
    srand(time(0));
    cout << "Enter total number of frames you want to simulate: ";
    cin >> totalFrames;
    cout << "Enter window size: ";
    cin >> windowSize;
    frames = new frame[totalFrames];
    for (int i = 0; i < totalFrames; i++)
    {
        cout << "Enter frame number " << i + 1 << " : ";
        cin >> frames[i].data;
        frames[i].seq = i % windowSize;
        frames[i].seq = (i + 1) % windowSize;
    }
}

Simulator::~Simulator()
{
    if (frames != NULL)
        delete[] frames;
}

void Simulator::sender(int from)
{
    int faultIndex = (rand() % windowSize) + from;
    int faultHappens = rand() % 5;
    for (int i = from; i < from + windowSize && i < totalFrames; i++)
    {
        if (i == faultIndex)
            continue;
        channel.push(frames[i]);
    }
    if (faultHappens == 0)
        sender(faultIndex);
}

void Simulator::reciever()
{
    while(!channel.empty)
    {
        cout<<"Recieved frame: "<<channel.front().data<<"; SEQ: "<<channel.front().seq;
    }
}

void Simulator::simulate()
{
    for(int i=0;i<totalFrames;i+=windowSize)
    {
        sender(i);
        reciever();
    }
}