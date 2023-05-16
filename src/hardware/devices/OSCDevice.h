#ifndef OSC_DEVICE_H
#define OSC_DEVICE_H

#include <io/network/udpSocket.h>
#include <io/network/address.h>
#include "hardware/hardwareOutputDevice.h"

#include <stdint.h>
#include <thread>

class OSCDevice : public HardwareOutputDevice
{
private:
    static constexpr int maximum_udp_packet_size = 65507;

    sp::io::network::UdpSocket socket;
    
    int channel_count;
    sp::io::network::Address address;
    int port_number;
    string osc_addresses[512];
    
public:
    OSCDevice();
    
    virtual bool configure(std::unordered_map<string, string> settings) override;

    virtual void setChannelData(int channel, float value) override;

    virtual int getChannelCount() override;

};

#endif//OSC_DEVICE_H
