#include<iostream>
#include<string>
#include<string.h>
//#include<boost/asio.hpp>

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

class Message{

    public:
        Message(): bodyLength_(0){}
        enum {maxBytes = 512};
        enum {header = 4};

        Message(std::string message){
            bodyLength_ = getNewBodyLength(message.size());
            encodeHeader();
            std::memcpy(data+header,message.c_str(),bodyLength_ );
        }

        size_t getNewBodyLength(size_t newLength){
            if(newLength >maxBytes){
                return maxBytes;
            }
            return newLength;
        }

        std:: string getData(){
            int length=header+bodyLength_;
            std::string result(data, length);
            return result;
        }

        std:: string getBody(){
            std::string dataString=getData();
            std::string result =dataString.substr(header,bodyLength_);
        }


        bool decodeHeader(){
            char newHeader[header+1]="";
            strncpy(newHeader,data,header);
            newHeader[header]='\0';
            int headerValue=atoi(newHeader);
            if(headerValue>maxBytes){
                bodyLength_ = 0;
                return false;
            }
            bodyLength_=headerValue;
            return true;
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


#endif MESSAGE_HPP

