#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"
#include "crc.h"
#include "setting.h"


class EsignUdp {
public:
    EsignUdp(string ip, int _port, int _port_count, int _cluster_count, int _data_size);
    ~EsignUdp();

    void setDebug(bool on);
    void setPixels(uint8_t red,uint8_t green, uint8_t blue);
    void setPixel(uint16_t channel, uint8_t red, uint8_t green, uint8_t blue);

    uint16_t sendto();

private:
    char* pixels;

    uint8_t port_count;
    uint16_t cluster_count;
    uint16_t data_size;

    bool isDumpPacket;

    ofxUDPManager udpConnection;
    int send_packet(uint8_t port_count, uint16_t cluster_count, uint8_t packet_size, uint8_t packet_index, uint16_t sent_datas, uint16_t data_size);
    void dump_packet(vector<unsigned char> packet);
};



