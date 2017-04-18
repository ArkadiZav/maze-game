#ifndef __OPENING_HEADER_H__
#define __OPENING_HEADER_H__

namespace maze
{
class Communication;

namespace colors
{
	const std::string LIGHT_BLUE = "\33[1;34m";
	const std::string NORMAL = "\033[0m";
	const std::string RED("\033[1;31m");
	const std::string YELLOW = "\033[1;93m";
	const std::string GREEN ("\033[1;32m");
	const std::string MAGNETA("\033[1;35m");
	static const std::string& DEFAULT_COLOUR = LIGHT_BLUE;
	static const size_t NUM_OF_COLORS = 6;
}

class Graphics
{
public:
	void ShowHeader(Communication* _com);
};

} //namespace maze

#endif // __OPENING_HEADER_H__
