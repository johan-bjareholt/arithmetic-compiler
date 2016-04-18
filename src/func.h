#include "nodes.h"
#include "variable.h"
#include "classes.h"

#include <string>

class Function : public Variable {
	public:
	ParlistNode* parlist;
	BlockNode* funcbody;

	std::string to_str();
	std::string to_asm();

	Function(ParlistNode& parlist, BlockNode& funcbody);
};
