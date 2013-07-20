#include "syntaxnode.h"
#include "bftokennames.h"
using namespace std;

SyntaxNode::SyntaxNode(TokenName & val, bool builds)
{
	value = &val;
	buildsCode = builds;
}

SyntaxNode(bool builds)
{
	buildsCode = builds;
}

void attachNext(SyntaxNode n)
{
	next.push_back(n);
}
