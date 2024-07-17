#ifndef API_BT_TREE_BT_Leaf_H
#define API_BT_TREE_BT_Leaf_H
#include <functional>
#include <memory>

#include "BtNode.h"



namespace behaviour_tree
{
	class BtLeaf final : public BtNode
	{

	private:
		std::function<Status()> leaf_action_;


	public:
		~BtLeaf() override = default;
		BtLeaf(const std::function<Status()>& leaf_action) : leaf_action_(leaf_action) {};

		Status Process() override;
		void reset() override {};

	};

	inline Status BtLeaf::Process()
	{

		//std::cout << "Leaf Process : " << name_ << std::endl;

		if (leaf_action_ != nullptr)
			return leaf_action_();
		else
			return Status::kFailure;

	}
}




#endif