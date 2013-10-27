#include <string>
#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include <reader.h>

using namespace binary_reader;

int main()
{
    //show_Message_binary_file_contents( BINARY_DIR "/2.4_example.in");
    //std::cout << std::endl;
{
    boost::shared_ptr<std::ifstream> input_file(new std::ifstream(BINARY_DIR "/input.txt", std::ifstream::binary));
    boost::shared_ptr<std::ofstream> output_file(new std::ofstream(BINARY_DIR "/output.txt", std::ofstream::binary));

    Message msg_max_time;
    while(input_file->is_open() && !input_file->eof())
	{
        Message msg;
        *input_file >> msg;
        if(!*input_file) // verify if stream is good
            break;
        if(msg.get_type()==0u || msg.get_type()>4u) // if message type is of interest
            continue;
        if(msg.get_time()+2u>msg_max_time.get_time()) // if message is not obsolete
            *output_file << msg;

        if(msg.get_time()>msg_max_time.get_time()) // update current time
            msg_max_time = msg;
	}
}
    //std::cout << std::endl;
    //show_Message_binary_file_contents( BINARY_DIR "/2.4.out");
}

