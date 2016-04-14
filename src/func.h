#include "nodes.h"
#include "variable.h"
#include "classes.h"

#include <string>

class Function : public Variable {
	public:
	ArglistNode* arglist;
	BlockNode* funcbody;

	std::string to_str();
	std::string to_asm();

	Function(ArglistNode& arglist, BlockNode& funcbody);
};
