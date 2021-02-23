#pragma once
#include "Component.h"

/*
	=====================================================================
							�ൿƮ����?
		root(�Ѹ�)�� ���� ���ϴµ��� ����(sequence, selector)�� ����
		��(�ൿ ���, Leaf)�� �ִ� �Լ��� �����ϴ� ���

		����: �б����� �� �������ָ� �˾Ƽ� ��Ȳ�� �´� �ൿ�� ��������ش�.
			  �б⳪ �ൿ ����� �߰� �� ������ �ſ� ����.
			 A �б⿡�� ����� �ൿ ��带 B �б⿡�� ����ϰ� ���� ��� �׳� �ൿ��带
			 �߰��ؼ� �ٿ��ֱ⸸ �ϸ� �ȴ�.(����/��Ȱ���� �����ϴ�)

		����: ���ʿ� �ִ� �ͺ��� ������� �Ǵ��Ͽ� �����ϱ� ������ ������ �� ������Ѵ�.

		## �𸮾󿡼��� �⺻������ �����ϴ� AI �����̴�. ���������� ���� ���̱� ������
		�˰� ������ ����!

		## C++�� List�� �˰� ������ �� �����ϱ� ����
		## List�� �˷��� ����Ʈ�� ������ �˾ƾ� �� ���ذ� ����
		## ����Ʈ�� ������ �˰��򿡼� ��! ��! ��! ������ �ʴ� ��ǥ �������� �����̴�!
		## �����صθ� ����!!
	=====================================================================

				<�ð�ȭ�� �ϸ� �Ʒ��� ���� �����̴�!>

						<root>
						/	\
					   /     \
					  /       \
					 /         \
					/           \
		 <sequence: �б���, ����> \
								  \
						 <selector: �б���, ����>
								   /\
								  /  \
								 /    \
								/      \
		<ActionNode: �ൿ ���, Leaf>    \
										 \
								<ActionNode: �ൿ ���, Leaf>
*/



class TransformC;

enum class STATE : int
{
	FAILURE,	// bool���� false
	SUCCESS,	// bool���� true
	RUNNING,
};


//==========================================================BehaviorTree===========================================================//

/*================================================================
							AI ���� Ŭ����
================================================================*/

class BT : public Component
{
protected:

	
public:
	BT() {};
	~BT() {};

	/*================================================================
					���¸� �����ϴ� �߻� Ŭ����
	================================================================*/
	class Node
	{
	protected:
		STATE _state;
		
	public:
		virtual STATE invoke() = 0;
	};

	//==========================================================CompositeNode===========================================================//

	/*================================================================
			�������� �ڽ����� ������ Node���� ������ �ִ� �ֻ��� Ŭ����
	================================================================*/
	class CompositeNode : public Node
	{
	private:
		list<Node*> lChildren;
	public:
		void AddChild(Node* node) { lChildren.emplace_back(node); }
		const list<Node*>& getChildren() { return lChildren; }
	};
	/*================================================================
						CompositeNode ī�װ� �� �ϳ�
							�б��� �� �ϳ�
				(���� ���� �߿��� �ϳ��� ������ �� ���)
	================================================================*/
	class Selector : public CompositeNode // �ϳ��� true�� true ��ȯ -> ���� �� false�� �ൿ ����
	{
	public:
		virtual STATE invoke() override
		{
			for (auto node : getChildren())
			{
				STATE temp = node->invoke();
				if (temp == STATE::RUNNING)
				{
					return STATE::RUNNING;
				}
				else if (temp == STATE::SUCCESS)
				{
					return STATE::SUCCESS;
				}
			}
			return STATE::FAILURE;
		}
	};

	/*================================================================
						CompositeNode ī�װ� �� �ϳ�
							�б��� �� �ϳ�
			(���� ������ �� �����ϴٰ� �ϳ��� false�Ǹ� ����)
	================================================================*/
	class Sequence : public CompositeNode // �ϳ��� false�� false ��ȯ -> ���� �� true�� �ൿ ����
	{
	public:
		virtual STATE invoke() override
		{
			for (auto node : getChildren())
			{
				STATE temp = node->invoke();
				if (temp == STATE::RUNNING)
				{
					return STATE::RUNNING;
				}
				if (temp == STATE::FAILURE)
				{
					return STATE::FAILURE;
				}
			}
			return STATE::SUCCESS;
		}
	};
	//=====================================================Decorator=========================================================//

	/*================================================================

						�ϳ��� �ڽĸ��� ������ �־
					���ǿ� ���� ����� ��ȯ�ϴ� �ֻ��� Ŭ����

	================================================================*/
	class DecoratorNode : public Node
	{
	private:
		Node* child;

	protected:
		Node* getChild() const { return child; }
	public:
		void AddChild(Node* node) { child = node; }
	};

	/*================================================================

				���ǿ� ���� �ڽ��� �����ϰų� ���и� ��ȯ

	================================================================*/
	class Condition : public DecoratorNode
	{
	private:
		function<bool(void)> fn;

	public:
		Condition() {};

		virtual STATE invoke() = 0;
	};

	class VoidCondition : public Condition
	{
	private:
		function<bool(void)> fn;

	public:
		VoidCondition(function<bool(void)> fn)
		{
			this->fn = fn;
		}
		virtual STATE invoke()
		{
			if (fn()) return getChild()->invoke();
			else return STATE::FAILURE;
		}
	};

	class StrCondition : public Condition
	{
	private:
		function<bool(string)> fn;
		string name;

	public:
		StrCondition(function<bool(string)> fn, string name)
		{
			this->fn = fn;
			this->name = name;
		}

		virtual STATE invoke()
		{
			if (fn(name)) return getChild()->invoke();
			else return STATE::FAILURE;
		}

	};

	class ToolCondition : public Condition
	{
	private:
		function<bool(TOOLTYPE)> fn;
		TOOLTYPE name;

	public:
		ToolCondition(function<bool(TOOLTYPE)> fn, TOOLTYPE name)
		{
			this->fn = fn;
			this->name = name;
		}

		virtual STATE invoke()
		{
			if (fn(name)) return getChild()->invoke();
			else return STATE::FAILURE;
		}

	};

	/*================================================================

						������ ������� �����Ͽ� ��ȯ

	================================================================*/
	class Inverter : public DecoratorNode
	{
	private:
		virtual STATE invoke() override
		{
			if (getChild()->invoke() == STATE::SUCCESS) return STATE::FAILURE;
			else if (getChild()->invoke() == STATE::FAILURE) return STATE::SUCCESS;
		}
	};

	/*================================================================

							�׻� ������ ��ȯ

	================================================================*/
	class Suceeder : public DecoratorNode
	{
	public:
		virtual STATE invoke() override
		{
			if (getChild()->invoke() == STATE::FAILURE) return STATE::SUCCESS;
			else if (getChild()->invoke() == STATE::SUCCESS) return STATE::SUCCESS;
		}
	};

	/*================================================================

						���и� ��ȯ�� ������ �ݺ� ����

	================================================================*/
	class RepeaterUntilFail : public DecoratorNode
	{
	public:
		virtual STATE invoke() override
		{
			while (getChild()->invoke() != STATE::FAILURE)
			{

			}
			return STATE::SUCCESS;
		}
	};

	//==========================================================ActionNode===========================================================//

	/*================================================================
							Node ī�װ� �� �ϳ�
				(���������� �ൿ �Լ��� ������ �����ϴ� Ŭ����)
	================================================================*/
	class ActionNode : public Node
	{

	};


	
};
