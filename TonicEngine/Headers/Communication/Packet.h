//
// Created by Lucas on 30/09/2018.
//

#ifndef PROJECT_SWA_IPACKET_H
#define PROJECT_SWA_IPACKET_H

#include <string>

class Packet{
private:
    const std::string content;
public:
    Packet(const std::string &content);
    ~Packet();

    std::string getContent() const{
        return content;
    }

};
#endif //PROJECT_SWA_IPACKET_H
