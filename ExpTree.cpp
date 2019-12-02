#include <iostream>
#include <string>
#include <stack>
using namespace std;
using int32 = int;

class ExpTree
{
public:
	bool bOperator = false;
	int32 Data = -1;
	ExpTree* Left = nullptr;
	ExpTree* Right = nullptr;
	int32 CalculateExp(ExpTree* Target)
	{
		   // if (Target->Left == nullptr || Target->Right== nullptr)return Target->Data;
		if (Target->Left == nullptr && Target->Right == nullptr) return Target->Data;
		
		int32 LhsData = CalculateExp(Target->Left);
		int32 RhsData = CalculateExp(Target->Right);
		
		int32 ReturnVal = 0;
		switch((char)this->Data)
		{
		case '+':
			ReturnVal = LhsData + RhsData;
			break;
		case '-':
			ReturnVal = LhsData  - RhsData;
			break;
		case '/':
			ReturnVal = LhsData  / RhsData;
			break;
		case '*':
			ReturnVal = LhsData * RhsData;
			break;
		}
		bOperator = false;
		this->Data = ReturnVal;
		return this->Data;
		 // return this->Data = ReturnVal;
	}
	static void Postfix(ExpTree* Root)
	{
		if(Root)
		{
			Postfix(Root->Left);
			
			if (Root->bOperator==true)
				cout << "Oper : " << (char)Root->Data << endl;
			else if (Root->bOperator==false)
			cout << "Num : " << Root->Data << endl;
			
			Postfix(Root->Right);
		}
	}
	static ExpTree* MakeExpTree(int32 SetData)
	{
		ExpTree* ReturnVal = new ExpTree;
		ReturnVal->Data = SetData;
		ReturnVal->Left = nullptr;
		ReturnVal->Right = nullptr;
		ReturnVal->bOperator = false;
		
		if(SetData=='+' || SetData=='-' || SetData =='/' || SetData =='*' )
		{
			ReturnVal -> bOperator = true;
		}
		return  ReturnVal;
	}
	static ExpTree* MakeExpTreeReturnRoot(std::string Expression)
	{
		auto Root = MakeExpTree((int32)Expression[0]);
		for(int32 i =1;i<Expression.size(); ++i)
		{
			if (Expression[i] == ' ')continue;
			Root->Push(MakeExpTree((int32)Expression[i]));
			
		}
		return Root;
		/*auto Root = MakeExpTree((int32)Expression[0]);
		Expression.erase(Expression[0]);
		
		for(const auto& Element : Expression )
		{
			if (Element == ' ')continue;
			Root->Push(MakeExpTree(Element));
		}
		return Root;*/
	}
	void Push(ExpTree* Target)
	{
		if (this->Left == nullptr)
		{
			Left = Target;
			return;
		}
		else if(this->Right ==nullptr)
		{
			Right = Target;
			return;
		}
		this->Left->Push(Target);
		
	}
};
class ExpStack
{
public:
	std::stack<ExpTree*> Stack;
	void Push (ExpTree* Target)
	{
		Stack.push(Target);
	}
};

int main()
{
	auto Root = ExpTree::MakeExpTree('+');
	
	auto RootLeft = ExpTree::MakeExpTree('+');
	
	auto RootRight = ExpTree::MakeExpTree('+');
	
	auto RootLeftLeft = ExpTree::MakeExpTree(11);
	auto RootLeftRight= ExpTree::MakeExpTree(22);
	
	auto RootRightLeft = ExpTree::MakeExpTree(33);
	auto RootRightRight  = ExpTree::MakeExpTree(44);
	
	//
	//Root->Left = RootLeft;
	//Root->Right = RootRight;
	//
	Root->Push(RootLeft);
	Root->Push(RootRight);

	Root->Left->Push(RootLeftLeft);
	Root->Left->Push(RootLeftRight );

	Root->Right->Push(RootRightLeft);
	Root->Right->Push(RootRightRight);
	
	Root->CalculateExp(Root);
	
	ExpTree::Postfix(Root);
	//std::string Expression = "1+2";
	//auto Root = ExpTree::MakeExpTreeReturnRoot(Expression);
	//Root->CalculateExp(Root);
	//ExpTree::Postfix(Root);
}
