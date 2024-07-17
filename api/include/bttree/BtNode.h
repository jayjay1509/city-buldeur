#ifndef API_BT_TREE_BT_NODE_H
#define API_BT_TREE_BT_NODE_H
#include <vector>

namespace behaviour_tree
{
	class BtLeaf;

	enum class Status
	{
		kRunning,
		kFailure,
		kSuccess
	};

	class BtNode
	{

	public:
		virtual ~BtNode() = default;
		virtual Status Process() = 0;
		virtual void reset() = 0;


	};

	class BtNodeList : public BtNode
	{
		

	protected:
		std::vector<BtNode*> children_;
		int current_child = 0;

	public:
		void AddNode(BtNode* node);
		void reset() override;


		~BtNodeList() override
		{
			for (auto& ptr :children_)
			{
				delete ptr;
			}
		}

	};

	inline void BtNodeList::AddNode(BtNode* node)
	{

		children_.push_back(node);
	}

	inline  void BtNodeList::reset()
	{
		current_child = 0;
	}


}
#endif