#ifndef API_BT_TREE_BT_seletor_H
#define API_BT_TREE_BT_seletor_H
#include "BtNode.h"


using namespace behaviour_tree;

class BtSelector : public BtNodeList
{
public:

	Status Process() override;

	~BtSelector() override = default;
};

inline  Status BtSelector::Process()
{
		if (current_child < children_.size())
		{
			const Status status = children_[current_child]->Process();

			if (status == Status::kFailure)
			{
				children_[current_child]->reset();

				current_child++;
				if (current_child >= children_.size())
				{
					current_child = 0;
					return Status::kFailure;
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