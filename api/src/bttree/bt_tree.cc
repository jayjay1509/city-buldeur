#include "bttree/bt_tree.h"

#include <iostream>

using namespace behaviour_tree;


BtTree::~BtTree()
{
	delete root_;
}

void BtTree::Tick()
{
	

	if (root_ != nullptr)
		Status status = root_->Process();

	/*switch (status) {
	case Status::kRunning:
		break;
	case Status::kFailure:
		break;
	case Status::kSuccess:
		break;
	default:
		std::cout << "Whaaaaaat ?????" << std::endl;
		break;
	}*/

}

void BtTree::AttachNode(BtNode* node)
{
	root_ = node;
}