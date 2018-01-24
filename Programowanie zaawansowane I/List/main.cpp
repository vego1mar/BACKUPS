#include <cstdio>
#include <cstdlib>

#include "Data.h"
#include "Node.h"
#include "List.h"

// ______________________________________________________________________________________

void Test_class_Data();
void Test_class_Node();
void Test_class_List();

// ______________________________________________________________________________________
// ______________________________________________________________________________________

int main()
{
Test_class_Data();
Test_class_Node();
Test_class_List();
puts("main() will end after a keystroke.");
getchar();
return (0);
};

// ______________________________________________________________________________________
// ______________________________________________________________________________________

void Test_class_Data()
{
printf("\n\n-----------------------------------------------------------------------\n"
       "                        Test_class_Data()\n"
       "-----------------------------------------------------------------------\n"
      );

Data D1("The parametric constructor Data(const char *) was run.");
Data D2("This text example that has more than 256 characters.\n"
        "This text example that has more than 256 characters.\n"
        "This text example that has more than 256 characters.\n"
        "This text example that has more than 256 characters.\n"
        "This text example that has more than 256 characters.\n"
        );
Data D3 = "The type conversion constructor was run here.";
Data D4 = '?';

printf("D1 = <%s>\n",D1.Get());
D1.Set("The new text has been set.");
printf("D1 = <%s>\n",D1.Get());
printf("D2 = <%s>\n",D2.Get());
printf("D3 = <%s>\n",D3.Get());
printf("D4 = <%s>\n",D4.Get());
D4.Set("!");
printf("D4 = <%s>\n",D4.Get());

puts("\nTest_class_Data() has been ended.");
getchar();
system("cls");
};

// ______________________________________________________________________________________

void Test_class_Node()
{
printf("\n\n-----------------------------------------------------------------------\n"
       "                        Test_class_Node()\n"
       "-----------------------------------------------------------------------\n"
      );

Node N1;
Node N2;
Node N3;

N1.SetData("This is the first node.");
N2.SetData("This is the second node.");
N3.SetData("An this is the third node.");
N1.SetNext(&N2);
N2.SetPrevious(&N1);
N2.SetNext(&N3);
N3.SetPrevious(&N2);
printf("N1(N1) = <%s>\n",N1.GetData());
printf("N2(N2) = <%s>\n",N2.GetData());
printf("N3(N3) = <%s>\n",N3.GetData());
putchar('\n');

const Node * N4 = N1.GetPrevious();
const Node * N5 = N1.GetNext();
const Node * N6 = N2.GetPrevious();
const Node * N7 = N2.GetNext();
const Node * N8 = N3.GetPrevious();
const Node * N9 = N3.GetNext();

printf("[N1(Prev) == NULL] = <%s>\n",N4->GetData());
printf("[N1(Next) == N2] = <%s>\n",N5->GetData());
printf("[N2(Prev) == N1] = <%s>\n",N6->GetData());
printf("[N2(Next) == N3] = <%s>\n",N7->GetData());
printf("[N3(Prev) == N2] = <%s>\n",N8->GetData());
printf("[N3(Next) == NULL] = <%s>\n",N9->GetData());

puts("\nTest_class_Node() has been ended.");
getchar();
system("cls");
};

// ______________________________________________________________________________________

void Test_class_List()
{
printf("\n\n-----------------------------------------------------------------------\n"
       "                        Test_class_List()\n"
       "-----------------------------------------------------------------------\n"
      );

List L;

L.AddNode(Data("Node 0."));
L.AddNode(Data("Node 1."));
L.AddNode(Data("Node 2."));
L.AddNode(Data("Node 3."));
L.AddNode(Data("Node 4."));

bool r1 = L.RemoveNode();
bool r2 = L.RemoveNode();
printf("RemoveNode() = <%d>\n",r1);
printf("RemoveNode() = <%d>\n",r2);
printf("NumberOfElements = <%u>\n",L.GetNumberOfElements());

const Node * tmp1 = L.GetFirstElement();
const Node * tmp2 = L.GetCurrentElement();
const Node * tmp3 = L.GetLastElement();
printf("FirstElementData = <%s>\n",tmp1->GetData());
printf("CurrentElementData = <%s>\n",tmp2->GetData());
printf("LastElementData = <%s>\n",tmp3->GetData());

puts("Rewind");
L.Rewind();
Node * tmp4 = L.GetNextElement();
printf("NextElementData = <%s>\n",tmp4->GetData());
tmp4 = L.GetPreviousElement();
printf("PreviousElementData = <%s>\n",tmp4->GetData());
tmp4 = L.GetPreviousElement();
printf("PreviousElementData = <%s>\n",tmp4->GetData());

Node & tmp5 = L.GetElementDataAt(-2);
printf("GetElementDataAt(-2) = <%s>\n",tmp5.GetData());
tmp5 = L.GetElementDataAt(0);
printf("GetElementDataAt(0) = <%s>\n",tmp5.GetData());

for (int i=1; i<6; i++)
    {
    tmp5 = L.GetElementDataAt(i);
    printf("GetElementDataAt(%d) = <%s>\n",i,tmp5.GetData());
    };

printf("ListSize = <%u>\n",L.GetListSize());
printf("NumberOfDeletedNodes = <%u>\n",L.GetNumberOfDeletedNodes());

for (int i=0; i<5; i++)
    {
    printf("List[%d] = <%s>\n",i,L[i]);
    };

puts("\nTest_class_List() has been ended.");
getchar();
system("cls");
};

// ______________________________________________________________________________________
