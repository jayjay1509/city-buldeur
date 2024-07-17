#ifndef API_BT_TREE_BT_sequence_H
#define API_BT_TREE_BT_sequence_H
#include "BtNode.h"

using namespace behaviour_tree;

class bt_sequence : public BtNodeList
{
public:
	
	~bt_sequence() override = default;

	Status Process() override;
};

inline Status bt_sequence::Process()
{

	if (current_child < children_.size())
	{
		const Status status = children_[current_child]->Process();

		if (status == Status::kSuccess)
		{
			//std::cout << "Next sequence !" << std::endl;

			children_[current_child]->reset();

			current_child++;
			if (current_child >= children_.size())
			{
				current_child = 0;
				return Status::kSuccess;
			}
			else
			{
				return Status::kRunning;
			}
		}

		return status;


	}

	return Status::kFailure;

}



#endif
