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
    queue<int> ACKS;
    frame *frames;
    int totalFrames;
    int windowSize;
    int faultIndex;
    int faultHappens;
    bool isNoisy;
  public:
    Simulator();
    ~Simulator();
    void sender(int from);
    void reciever();
    void recieveACK();
    void simulate(bool isNoisy = false);
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
    }
    isNoisy = false;
}

Simulator::~Simulator()
{
    if (frames != NULL)
        delete[] frames;
}

void Simulator::sender(int from)
{
    if (isNoisy)
    {
        faultIndex = (rand() % totalFrames);
        faultHappens = rand() % 2;
    }
    else
    {
        faultHappens = 1;
    }
    for (int i = from; i < from + windowSize && i < totalFrames; i++)
    {
        if (i == faultIndex && faultHappens == 0)
            continue;
        cout << "SENDER: sent frame " << frames[i].data << " SEQ: " << frames[i].seq << endl;
        channel.push(frames[i]);
        ACKS.push(frames[i].seq);
    }
}

void Simulator::reciever()
{
    while (!channel.empty())
    {
        cout << "RECIEVER: Recieved frame: " << channel.front().data << " SEQ: " << channel.front().seq << endl;
        channel.pop();
    }
}

void Simulator::recieveACK()
{
    while (!ACKS.empty())
    {
        cout << "SENDER: Recieved ACK for frame SEQ: " << ACKS.front() << endl;
        ACKS.pop();
    }
    if (faultHappens == 0)
    {
        cout << "SENDER: Haven't Recieved ack for frame: " << frames[faultIndex].seq << endl;
        cout << "SENDER: Resending frames... from SEQ: " << frames[faultIndex].seq << endl;
        sender(faultIndex);
        reciever();
        recieveACK();
    }
}

void Simulator::simulate(bool isNoisy)
{
    this->isNoisy = isNoisy;
    for (int i = 0; i < totalFrames; i += windowSize)
    {
        sender(i);
        reciever();
        recieveACK();
    }
}