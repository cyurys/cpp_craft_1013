#ifndef _BINARY_READER_READER_H_
#define _BINARY_READER_READER_H_

// this #ifndef + #define + #endif called header (include) guards:
// http://ru.wikipedia.org/wiki/Include_guard

#include <boost/cstdint.hpp>
#include <string>
#include <fstream>
namespace binary_reader
{
	class Message
	{
		boost::uint32_t TYPE, TIME, LEN;
		std::string MSG;
	public:
		boost::uint32_t get_time() const;
        boost::uint32_t get_type() const;
		Message(uint32_t TYPE=0, uint32_t TIME=0, uint32_t LEN=0, std::string MSG="");
		~Message();

        void show();
        friend std::ifstream& operator>>(std::ifstream&, Message&);
        friend std::ofstream& operator<<(std::ofstream&, Message const &);
	};
        std::ifstream& operator>>(std::ifstream&, Message&);
        std::ofstream& operator<<(std::ofstream&, Message const &);

    // useful for debugging to see the contents of binary file of Message objects
    void show_Message_binary_file_contents(const char* filename);

	void proxy_function_that_was_created_only_for_compiling_goals();
}

#endif // _BINARY_READER_READER_H_
