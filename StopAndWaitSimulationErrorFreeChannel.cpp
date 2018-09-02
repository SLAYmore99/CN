#include <iostream>
#include <cstdlib>
#include <cstring>

#ifdef __linux__
#define CLRSCR "clear"
#else
#define CLRSCR "cls"
#endif

using namespace std;

const int MAX_SIZE = 256; //max size of data

class packet //packet class
{
    char data[MAX_SIZE];
    friend class StopAndWaitSimulator;
public:
    packet()
    {
        strcpy(data,"");
    }
};

class frame //frame class
{
    packet info;
    int ack;
    friend class StopAndWaitSimulator;
};

enum event_type
{
    RECIEVED_FRAME,
};

class StopAndWaitSimulator
{
    frame frameInPhysicalLayer;
    int numOfFrames;
    void sender();
    void reciever();
    void fromNetworkLayer(packet *);
    void toNetworkLayer(packet *);
    void fromPhysicalLayer(frame *);
    void toPhysicalLayer(frame *);
    void waitForEvent(event_type *);

  public:
    StopAndWaitSimulator(int num_of_frames);
    void simulate();
};

int main()
{
    int numOfFrames;
    cout << "Enter number of frames you want to simulate: ";
    cin >> numOfFrames;
    StopAndWaitSimulator saws(numOfFrames);
    saws.simulate();
    return 0;
}

StopAndWaitSimulator::StopAndWaitSimulator(int numOfFrames)
{
    this->numOfFrames = numOfFrames;
}

void StopAndWaitSimulator::fromNetworkLayer(packet *pckt)
{
    cout << "Enter data to transmit in packet: ";
    cin >> pckt->data;
}

void StopAndWaitSimulator::toNetworkLayer(packet *pckt)
{
    cout << "RECIEVER: Recieved packet contating data: " << pckt->data << endl;
    cout<<"Press enter to continue...";
    cin.ignore();
    cin.get();
}

void StopAndWaitSimulator::toPhysicalLayer(frame *fram)
{
    strcpy(frameInPhysicalLayer.info.data,fram->info.data);
}

void StopAndWaitSimulator::fromPhysicalLayer(frame *fram)
{
    *fram = this->frameInPhysicalLayer;
}

void StopAndWaitSimulator::waitForEvent(event_type *evnt)
{
}

void StopAndWaitSimulator::sender()
{
    frame fram;
    packet pckt;
    event_type event;
    fromNetworkLayer(&pckt);
    fram.info = pckt;
    toPhysicalLayer(&fram);
    cout << "SENDER: Sent frame containing data: " << fram.info.data << endl;
    waitForEvent(&event);
}

void StopAndWaitSimulator::reciever()
{
    frame frameS, frameR;
    event_type event;
    waitForEvent(&event);
    fromPhysicalLayer(&frameR);
    toNetworkLayer(&frameR.info);
    toPhysicalLayer(&frameS);
}

void StopAndWaitSimulator::simulate()
{
    for (int i = 0; i < this->numOfFrames; i++)
    {
        system(CLRSCR);
        this->sender();
        this->reciever();
    }
}