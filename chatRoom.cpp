#include"chatRoom.hpp""


#ifndef CHATROOM_CPP
#define CHATROOM_CPP

void Room::join(ParticipantPointer participant){
       this->participants.insert(participant);
}

void Room::leave(ParticipantPointer participant){
       this->participants.erase(participant);
}

void Room ::deliver(ParticipantPointer participant, Message &message){
    messageQueue.push_back(message);

    while(!messageQueue.empty()){
       Message msg=messageQueue.front();
       messageQueue.pop_front();

          for(ParticipantPointer _participant:participants){
            if(participant!=_participant){
                 _participant->write(msg);
            }
          }
    }
}

void Session ::write(Message &message){
     messageQueue.push_back(message);
     while(messageQueue.size()!=0){
         Message msg=messageQueue.front();
         messageQueue.pop_front();
         bool headerDecoded=message.decodeHeader();
         if(headerDecoded){
                std::string body=message.getBody();
                async_write(body,message.getBodyLength());

         }else{
                std::cout<<"Message length exceeds the max length 512 characters"<<std::endl;
         }
     }
}



void Session :: deliver(Message &message){
        room.deliver(shared_from_this(),message);
}

void Session :: start(){
       room.join(shared_from_this());
       async_read();

}

using boost ::asio ::ip::address_v4;

void accept_connection(boost::asio::io_context &io, char *port,tcp::)

#endif CHATROOM_CPP
