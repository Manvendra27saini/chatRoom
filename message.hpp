//--> how to remotely connect to UTM(for mac) ubuntu server from vscode ,for windows wsl
#include<iostream>
#include<string>
#include<string.h>
//#include<boost/asio.hpp>


#ifndef MESSAGE_HPP
#define MESSAGE_HPP

//using boost::asio::ip::tcp;

class Message{

    public:
        Message(): bodyLength_(0){}
        enum {maxBytes = 512};
        enum {header = 4};

        Message(std::string message){
            bodyLength_ = getNewBodyLength(message.size());
            encodeHeader();
        }

        size_t getNewBodyLength(size_t newLength){
            if(newLength >maxBytes){
                return maxBytes;
            }
            return newLength;
        }

        void encodeHeader(){
            char newHeader[header+1]="";
            sprintf(newHeader, "%4f",static_cast<int>(bodyLength_));
            memcpy(data,newHeader,header);
        }

    private:
        char data[header+maxBytes];
        size_t bodyLength_;
};











#endif

