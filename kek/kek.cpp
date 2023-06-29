#include <iostream>
#include <ostream>
#include <string.h>
#include <time.h>
#include <Windows.h>

using namespace std;
class Visitor
{
	string name;
public:

	Visitor() :Visitor(" ") {};
	Visitor(string name) :name{ name }{};
	Visitor(const Visitor& visitor);
	~Visitor() {};

	friend class PriQueue;

	Visitor& operator = ( Visitor&& dying);
	friend ostream& operator <<(ostream& out, const Visitor& visitor);

};
Visitor::Visitor(const Visitor& visitor)
{
	name = visitor.name;
}
ostream& operator<<(ostream& out, const Visitor& visitor)
{
	out << visitor.name;
	return out;
}

Visitor& Visitor::operator=( Visitor &&dying)
{
	name = dying.name;
	dying.name = " ";
	return *this;
}
;
class PriQueue
{
	Visitor* visitors;
	int *pri;
	int MaxPriQueueLength;
	int PriQueueLength;
public:
	static int time;
	PriQueue(int size);
	~PriQueue();
	void Add(Visitor &visitor, int pri);
	Visitor& Extract();
	void ExtractionPrint(Visitor& visitor, int pri);
	string PriorityCheck(int pri);
	void Clear();
	bool IsEmpty();
	bool IsFull();
	int GetCount();
	void Show();
	friend class Visitor;
};
int PriQueue::time = 0;

PriQueue::PriQueue(int size)
{
	MaxPriQueueLength = size;
	visitors = new Visitor[MaxPriQueueLength];
	pri = new int[MaxPriQueueLength];
	PriQueueLength = 0;
}

PriQueue::~PriQueue()
{
	delete[] visitors;
}

void PriQueue::Add( Visitor &visitor, int p)
{
	if (!IsFull())
	{
		visitors[PriQueueLength] = move(visitor);
		pri[PriQueueLength] = p;
		PriQueueLength++;
	}
}

Visitor& PriQueue::Extract()
{
	if (!IsEmpty())
	{
		int max_pri = pri[0];
		int pos_max_pri = 0;
		for (int i = 1; i < PriQueueLength; i++)
		{
			if (max_pri < pri[i])
			{
				max_pri = pri[i];
				pos_max_pri = i;
			}
		}
		Visitor temp1 = visitors[pos_max_pri];
		int temp2 = pri[pos_max_pri];

		for (int i = pos_max_pri; i < PriQueueLength - 1; i++)
		{
			visitors[i] = move(visitors[i + 1]);
			pri[i] = pri[i + 1];
		}
		PriQueueLength--;
		time += 5;
		ExtractionPrint(temp1, temp2);
		return temp1;
	}
	
	else
	{
		cout << "Queue Is empty!";
		abort();
	};
}

void PriQueue::ExtractionPrint(Visitor& visitor, int pri)
{
	cout << "Printing complete for " << visitor.name << " with "<< PriorityCheck(pri)<<" ";
	cout << "priority for a " << time << " minutes " << endl;
}

string PriQueue::PriorityCheck(int pri)
{
	switch (pri)
	{
	case 0: return "Visitor "; break;
	case 1: return "Worker "; break;
	case 2: return "Administrator "; break;
	case 3: return "Boss "; break;
	}
}

void PriQueue::Clear()
{
	PriQueueLength = 0;
}

bool PriQueue::IsEmpty()
{
	return PriQueueLength == 0;
}

bool PriQueue::IsFull()
{
	return PriQueueLength == MaxPriQueueLength;
}

int PriQueue::GetCount()
{
	return PriQueueLength;
}

void PriQueue::Show()
{
	for (int i = 0; i < PriQueueLength; i++)
	{
		cout << visitors[i]<<" - "<<PriorityCheck(pri[i]) << endl;
	}
	cout << endl;
}
int main()
{
	Visitor vis1("Michael");
	Visitor vis2("Masha");
	Visitor vis3("Nikita");
	Visitor vis4("Josh");
	Visitor vis5("Pasha");

	PriQueue PrinterQueue(10);

	PrinterQueue.Add(vis1, 2);
	PrinterQueue.Add(vis2, 1);
	PrinterQueue.Add(vis3, 2);
	PrinterQueue.Add(vis4, 3);
	PrinterQueue.Add(vis5, 0);

	cout << "All clients:" << endl;
	PrinterQueue.Show();
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	while (!PrinterQueue.IsEmpty())
	{
		PrinterQueue.Extract();
		Sleep(2000);
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	
}


