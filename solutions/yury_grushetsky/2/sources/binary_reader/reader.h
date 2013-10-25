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
		Message(uint32_t TYPE=0, uint32_t TIME=0, uint32_t LEN=0, std::string MSG="");
		~Message();

		friend std::istream& operator>>(std::istream&, Message&);
		friend std::ostream& operator<<(std::ostream&, Message const &);
	};
		std::istream& operator>>(std::istream&, Message&);
		std::ostream& operator<<(std::ostream&, Message const &);

	void proxy_function_that_was_created_only_for_compiling_goals();
}

#endif // _BINARY_READER_READER_H_
