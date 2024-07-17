#ifndef API_BT_TREE_BT_Tree_H
#define API_BT_TREE_BT_Tree_H
#include <memory>

#include "BtNode.h"


namespace behaviour_tree
{
	class BtTree
	{
		BtNode* root_ = nullptr;

	public:
	

		~BtTree();

		void Tick();
		void AttachNode(BtNode* node);

	};

}

#endif