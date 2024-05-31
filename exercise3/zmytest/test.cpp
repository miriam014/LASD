
#ifndef MYTEST_CPP
#define MYTEST_CPP

/* ************************************************************************** */

#include <iostream>
#include <random>

#include "test.hpp"

#define DimensioneContainer 10

using namespace std;


default_random_engine gen(random_device{}());
uniform_int_distribution<int> RandomNumber(1, 100);



/* ************************************************************************** */
//COPY and MOVE assignment 

bool CopyAssignmentVec() {
  lasd::Vector<int> s1(RandomNumber(gen)); 
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=RandomNumber(gen);    

  lasd::Vector<int> s2(RandomNumber(gen));  
  for(ulong i=0; i<s2.Size(); i++) 
    s2[i]=RandomNumber(gen);

  s1 = s2;   
  return (s1==s2);
}

bool MoveAssignmentVec() {
  lasd::Vector<int> s1(RandomNumber(gen)); 
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=RandomNumber(gen);    

  lasd::Vector<int> s2;
  s2=s1; 

  lasd::Vector<int> s3;
  s3 = move(s2);
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyAssignmentList() {
  int size1 = RandomNumber(gen);
  int size2 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++)
      s1.InsertAtBack(RandomNumber(gen));
  
  lasd::List<int> s2;
  for(int i=0; i<size2; i++)
      s2.InsertAtBack(RandomNumber(gen));
  
  s1 = s2;
  return (s1==s2);
}

bool MoveAssignmentList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::List<int> s2; 
  s2=s1;

  lasd::List<int> s3;  
  s3 = move(s2);
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyAssignmentQueueVec() {
  int size1 = RandomNumber(gen);
  int size2 = RandomNumber(gen);
  lasd::QueueVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));

  lasd::QueueVec<int> s2;
  for(int i=0; i<size2; i++) 
    s2.Enqueue(RandomNumber(gen));

  s1 = s2;
  return (s1==s2);
}

bool MoveAssignmentQueueVec() {
  int size1 = RandomNumber(gen);
  lasd::QueueVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));
  //creo un secondo vettore dove copio il primo
  lasd::QueueVec<int> s2; 
  s2=s1;

  lasd::QueueVec<int> s3;  
  s3 = move(s2);
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}



bool CopyAssignmentQueueList() {
  int size1 = RandomNumber(gen);
  int size2 = RandomNumber(gen);
  lasd::QueueLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));

  lasd::QueueLst<int> s2;
  for(int i=0; i<size2; i++) 
    s2.Enqueue(RandomNumber(gen));

  s1 = s2;
  return (s1==s2);
}

bool MoveAssignmentQueueList() {
  int size1 = RandomNumber(gen);
  lasd::QueueLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));

  lasd::QueueLst<int> s2;
  s2=s1;

  lasd::QueueLst<int> s3;
  s3 = move(s2);
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyAssignmentStackVec() {
  int size1 = RandomNumber(gen);
  int size2 = RandomNumber(gen);
  lasd::StackVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackVec<int> s2;
  for(int i=0; i<size2; i++) 
    s2.Push(RandomNumber(gen));

  s1 = s2;
  return (s1==s2);
}

bool MoveAssignmentStackVec() {
  int size1 = RandomNumber(gen);
  lasd::StackVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackVec<int> s2;
  s2=s1;

  lasd::StackVec<int> s3;
  s3 = move(s2);
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyAssignmentStackList() {
  int size1 = RandomNumber(gen);
  int size2 = RandomNumber(gen);
  
  lasd::StackLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackLst<int> s2;
  for(int i=0; i<size2; i++) 
    s2.Push(RandomNumber(gen));
    
  s1 = s2;
  return (s1==s2);
}

bool MoveAssignmentStackList() {
  int size1 = RandomNumber(gen);
  lasd::StackLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackLst<int> s2;
  s2=s1;

  lasd::StackLst<int> s3;
  s3 = move(s2);
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


//********************************************************************************
//COPY and MOVE constructors

bool CopyConstructorVec() {
  lasd::Vector<int> s1(RandomNumber(gen)); 
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=RandomNumber(gen);    

  lasd::Vector<int> s2(s1);   
  return (s1==s2);
}

bool MoveConstructorVec() {
  lasd::Vector<int> s1(RandomNumber(gen)); 
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=RandomNumber(gen);    

  lasd::Vector<int> s2(s1); 

  lasd::Vector<int> s3(move(s2));

  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyConstructorList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++)
      s1.InsertAtBack(RandomNumber(gen));
  
  lasd::List<int> s2(s1);
  return (s1==s2);
}

bool MoveConstructorList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::List<int> s2(s1);

  lasd::List<int> s3(move(s2));
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyConstructorStackVec() {
  int size1 = RandomNumber(gen);
  lasd::StackVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackVec<int> s2(s1);
  return (s1==s2);
}

bool MoveConstructorStackVec() {
  int size1 = RandomNumber(gen);
  lasd::StackVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackVec<int> s2(s1);

  lasd::StackVec<int> s3(move(s2));
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyConstructorStackLst() {
  int size1 = RandomNumber(gen);
  lasd::StackLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackLst<int> s2(s1);
  return (s1==s2);
}

bool MoveConstructorStackLst() {
  int size1 = RandomNumber(gen);
  lasd::StackLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Push(RandomNumber(gen));

  lasd::StackLst<int> s2(s1);

  lasd::StackLst<int> s3(move(s2));
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyConstructorQueueVec() {
  int size1 = RandomNumber(gen);
  lasd::QueueVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));

  lasd::QueueVec<int> s2(s1);
  return (s1==s2);
}

bool MoveConstructorQueueVec() {
  int size1 = RandomNumber(gen);
  lasd::QueueVec<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));

  lasd::QueueVec<int> s2(s1);

  lasd::QueueVec<int> s3(move(s2));
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}


bool CopyConstructorQueueLst() {
  int size1 = RandomNumber(gen);
  lasd::QueueLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));

  lasd::QueueLst<int> s2(s1);
  return (s1==s2);
}

bool MoveConstructorQueueLst() {
  int size1 = RandomNumber(gen);
  lasd::QueueLst<int> s1;
  for(int i=0; i<size1; i++) 
    s1.Enqueue(RandomNumber(gen));

  lasd::QueueLst<int> s2(s1);

  lasd::QueueLst<int> s3(move(s2));
  if((s3==s1) && (s2.Empty()))
    return true;
  return false;
}

//lista da vett
bool CopyConstructorListVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++)
      s1[i]= (RandomNumber(gen));
  
  lasd::List<int> s2(s1);
  for(ulong i=0; i<s2.Size(); i++){
      if(s1[i]!=s2[i])
        return false;
  }
  return (true);
}

bool MoveConstructorLstVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++)
      s1[i]= (RandomNumber(gen));
  
  lasd::List<int> s2(s1);
  lasd::List<int> s3(move(s1));
  for(ulong i=0; i<s3.Size(); i++){
      if(s3[i]!=s2[i])
        return false;
  }
  return (true);
}

//vett da lista
bool CopyConstructorVecList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++)
      s1.InsertAtBack(RandomNumber(gen));
  
  lasd::Vector<int> s2(s1);
  for(ulong i=0; i<s2.Size(); i++){
      if(s1[i]!=s2[i])
        return false;
  }
  return true;
}

bool MoveConstructorVecLst() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++)
      s1.InsertAtBack(RandomNumber(gen));
  
  lasd::Vector<int> s2(s1);
  lasd::Vector<int> s3(move(s1));
  for(ulong i=0; i<s2.Size(); i++){
      if(s3[i]!=s2[i])
        return false;
  }
  return true;
}

//stackVec da Vett
bool CopyConstructorStackVecVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=RandomNumber(gen);

  lasd::StackVec<int> s2(s1);
  for(long i= s1.Size()-1; i>=0; i--){
      if(s1[i]!=s2.TopNPop())
        return false;
  }
  return true;
}

bool MoveConstructorStackVecVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=(RandomNumber(gen));

  lasd::StackVec<int> s2(s1);
  lasd::StackVec<int> s3(move(s1));
  for(long i= s3.Size()-1; i>=0; i--){
      if((s3.TopNPop()) != (s2.TopNPop()))
        return false;
  }
  return true;
}

//stackLst da Lista
bool CopyConstructorStackLstVec() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::StackVec<int> s2(s1);
  for(long i= s1.Size()-1; i>=0; i--){
      if(s1[i]!=s2.TopNPop())
        return false;
  }
  return true;
}

bool MoveConstructorStackLstVec() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::StackVec<int> s2(s1);
  lasd::StackVec<int> s3(move(s1));
  for(long i= s3.Size()-1; i>=0; i--){
      if((s3.TopNPop()) != (s2.TopNPop()))
        return false;
  }
  return true;
}

//queueLst da Vett
bool CopyConstructorQueueLstVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i] = RandomNumber(gen);

  lasd::QueueLst<int> s2(s1);
  for(ulong i=0; i<s2.Size(); i++){
      if(s1[i]!=s2.HeadNDequeue())
        return false;
  }
  return true;
}

bool MoveConstructorQueueLstVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i] = RandomNumber(gen);

  lasd::QueueLst<int> s2(s1);
  lasd::QueueLst<int> s3(move(s1));
  for(ulong i=0; i<s3.Size(); i++){
      if((s3.HeadNDequeue())!= (s2.HeadNDequeue()))
        return false;
  }
  return true;
}

//queueVec da vett
bool CopyConstructorQueueVecVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=(RandomNumber(gen));

  lasd::QueueVec<int> s2(s1);
  for(ulong i=0; i<s1.Size(); i++){
      if(s1[i]!=s2.HeadNDequeue())
        return false;
  }
  return true;
}

bool MoveConstructorQueueVecVec() {
  lasd::Vector<int> s1(RandomNumber(gen));
  for(ulong i=0; i<s1.Size(); i++) 
    s1[i]=(RandomNumber(gen));

  lasd::QueueVec<int> s2(s1);
  lasd::QueueVec<int> s3(move(s1));
  for(ulong i=0; i<s3.Size(); i++){
      if((s3.HeadNDequeue()) != (s2.HeadNDequeue()))
        return false;
  }
  return true;
}

//stackVec da Lista
bool CopyConstructorStackVecList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::StackVec<int> s2(s1);
  for(long i= s1.Size()-1; i>=0; i--){
      if(s1[i] != s2.TopNPop())
        return false;
  }
  return true;
}

bool MoveConstructorStackVecLst() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::StackVec<int> s2(s1);
  lasd::StackVec<int> s3(move(s1));
  for(long i= s3.Size()-1; i>=0; i--){
      if((s3.TopNPop()) != (s2.TopNPop()))
        return false;
  }
  return true;
}


//stackLst da Lista
bool CopyConstructorStackLstList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::StackLst<int> s2(s1);
  for(long i= s1.Size()-1; i>=0; i--){
      if(s1[i] != s2.TopNPop())
        return false;
  }
  return true;
}

bool MoveConstructorStackLstLst() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtBack(RandomNumber(gen));

  lasd::StackLst<int> s2(s1);
  lasd::StackLst<int> s3(move(s1));
  for(long i= s1.Size()-1; i>=0; i--){
      if((s3.TopNPop()) != (s2.TopNPop()))
        return false;
  }
  return true;
}

//queueLst da Lista
bool CopyConstructorQueueLstList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtFront(RandomNumber(gen));

  lasd::QueueLst<int> s2(s1);
  for(ulong i=0; i<s2.Size(); i++){
      if(s1[i]!=s2.HeadNDequeue())
        return false;
  }
  return true;
}

bool MoveConstructorQueueLstLst() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtFront(RandomNumber(gen));

  lasd::QueueLst<int> s2(s1);
  lasd::QueueLst<int> s3(move(s1));
  for(ulong i=0; i<s3.Size(); i++){
      if((s3.HeadNDequeue()) != (s2.HeadNDequeue()))
        return false;
  }
  return true;
}

//queueVec da Lista
bool CopyConstructorQueueVecList() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtFront(RandomNumber(gen));

  lasd::QueueVec<int> s2(s1);
  for(ulong i=0; i<s2.Size(); i++){
      if(s1[i]!=s2.HeadNDequeue())
        return false;
  }
  return true;
}

bool MoveConstructorQueueVecLst() {
  int size1 = RandomNumber(gen);
  lasd::List<int> s1;
  for(int i=0; i<size1; i++) 
    s1.InsertAtFront(RandomNumber(gen));

  lasd::QueueVec<int> s2(s1);
  lasd::QueueVec<int> s3(move(s1));
  for(ulong i=0; i<s3.Size(); i++){
      if((s3.HeadNDequeue()) != (s2.HeadNDequeue()))
        return false;
  }
  return true;
}

//********************************************************************************************
//LISTE

void RemoveEmptyList() {
lasd::List<int> list;
    try {
      list.RemoveFromFront(); // Should throw an exception
    } catch (const std::length_error& e) {
      std::cout << e.what() << std::endl;
    }
    
    list.InsertAtBack(10);
    list.InsertAtBack(20);
    list.RemoveFromFront();
    list.RemoveFromFront();
    
    try {
      list.RemoveFromFront(); // Should throw an exception
    } catch (const std::length_error& e) {
      std::cout << e.what() << std::endl;
    }
}

// Test InsertAtFront
bool InsertAtFront() {
    bool rispo;
    lasd::List<int> list1;
    list1.InsertAtFront(10);
    if (list1.Front() == 10 && list1.Back() == 10 && list1.Size() == 1)
        rispo = true;
    else rispo = false; 

    list1.InsertAtFront(20);
    if (list1.Front() == 20 && list1.Back() == 10 && list1.Size() == 2)
        rispo += true;
    else rispo += false;
    return rispo;
}


  // Test InsertAtBack
  bool InsertAtBack() {
    bool rispo;
  lasd::List<int> list2;
  list2.InsertAtBack(10);
  if (list2.Front() == 10 && list2.Back() == 10 && list2.Size() == 1)
      rispo = true;
  else
      rispo = false;
  list2.InsertAtBack(20);
  if (list2.Front() == 10 && list2.Back() == 20 && list2.Size() == 2)
      rispo += true;
  else
      rispo += false;
  return rispo;
  }

  // Test RemoveFromFront
  bool RemoveFromFront() {
    bool rispo;
  lasd::List<int> list3;
  list3.InsertAtFront(10);
  list3.InsertAtFront(20);
  list3.RemoveFromFront();
  if (list3.Front() == 10 && list3.Size() == 1)
      rispo = true;
  else
      rispo = false;

  list3.RemoveFromFront();
  if (list3.Size() == 0)
      rispo += true;
  else
      rispo += false;
  return rispo;
}


  // Test RemoveSpecificElement
  bool RemoveSpecificElement() {
    bool rispo;
  lasd::List<int> list4;
  list4.InsertAtBack(10);
  list4.InsertAtBack(20);
  list4.InsertAtBack(30);

  if (list4.Remove(20) && list4.Size() == 2 && list4.Front() == 10 && list4.Back() == 30)
      rispo = true;
  else
      rispo = false;

  if (!list4.Remove(40) && list4.Size() == 2)
      rispo += true;
  else
      rispo += false;
  return rispo;
  }


  // Test SwapLists
  bool SwapLists() {
  lasd::List<int> list11;
  list11.InsertAtBack(10);
  list11.InsertAtBack(20);
  lasd::List<int> list12;
  list12.InsertAtBack(30);
  list12.InsertAtBack(40);
  std::swap(list11, list12);
  if (list11.Front() == 30 && list11.Back() == 40 && list12.Front() == 10 && list12.Back() == 20)
      return true;
  else
      return false;
  }


//********************************************************************************
//ITERATORI

bool TestIteratori() {
  bool testIteratori = true;
  int lines = 1;
  cout<<"\n\nBegin of (BST into) Iterator Test: "<<endl;

  lasd::BinaryTreeLnk<int> btlnk;
  lasd::BTInOrderIterator<int> inOrderBSTlnk(btlnk);
  if(inOrderBSTlnk.Terminated()) {
    cout<<lines++<<" Iterator is terminated: Correct!"<<endl;
  } else {
    cout<<lines++<<"Iterator is not terminated: Error!"<<endl;
    testIteratori &= false;
  }
  lasd::BTInOrderIterator<int> inOrderBSTmovelnk(std::move(btlnk));
  if(inOrderBSTmovelnk.Terminated()) {
    cout<<lines++<<" Iterator is terminated: Correct!"<<endl;
  } else {
    cout<<lines++<<" Iterator is not terminated: Error!"<<endl;
    testIteratori &= false;
  }

  lasd::BinaryTreeVec<int> btvec;
  lasd::BTInOrderIterator<int> inOrderBSTvec(btvec);
  if(inOrderBSTvec.Terminated()) {
    cout<<lines++<<" Iterator is terminated: Correct!"<<endl;
  } else {
    cout<<lines++<<"Iterator is not terminated: Error!"<<endl;
    testIteratori &= false;
  }
  lasd::BTInOrderIterator<int> inOrderBSTmovevec(std::move(btvec));
  if(inOrderBSTmovevec.Terminated()) {
    cout<<lines++<<" Iterator is terminated: Correct!"<<endl;
  } else {
    cout<<lines++<<" Iterator is not terminated: Error!"<<endl<<endl;
    testIteratori &= false;
  }

//***************
  lasd::List<int> lst;
  for(int i=0; i<6; i++) {
    lst.InsertAtBack(i);
  }

  lasd::BinaryTreeLnk<int> btLnk(lst);

  cout<<"MAP:"<<endl;
  cout<<"Expected: 0->1->3->4->2->5->"<<endl;
  cout<<"Map ottenuta: ";
  btLnk.Map(
    [](int& dat){
      cout<<dat<<"->";
    }
  );
  cout<<endl<<endl;

  cout<<"PRE_ORDER_MAP:"<<endl;
  cout<<"Expected: 0->1->3->4->2->5->"<<endl;
  cout<<"PreOrderMap: ";
  btLnk.PreOrderMap(
    [](int& dat){
      cout<<dat<<"->";
    }
  );
  lasd::BTPreOrderIterator<int> itrPre(btLnk);
  cout<<"\nPreOrderIterator: ";
  while(!(itrPre.Terminated())){
    cout<<*itrPre<<"->";
    ++itrPre;
  }
  cout<<endl<<endl;

  cout<<"POST_ORDER_MAP:"<<endl;
  cout<<"Expected: 3->4->1->5->2->0->"<<endl;
  cout<<"PostOrderMap: ";
  btLnk.PostOrderMap(
    [](int& dat){
      cout<<dat<<"->";
    }
  );
  lasd::BTPostOrderIterator<int> itrPost(btLnk);
  cout<<"\nPostOrderIterator: ";
  while(!(itrPost.Terminated())){
    cout<<*itrPost<<"->";
    ++itrPost;
  }
  cout<<endl<<endl;

  cout<<"IN_ORDER_MAP:"<<endl;
  cout<<"Expected: 3->1->4->0->5->2->"<<endl;
  cout<<"InOrderMap: ";
  btLnk.InOrderMap(
    [](int& dat){
      cout<<dat<<"->";
    }
  );
  lasd::BTInOrderIterator<int> itrIn(btLnk);
  cout<<"\nInOrderIterator: ";
  while(!(itrIn.Terminated())){
    cout<<*itrIn<<"->";
    ++itrIn;
  }
  cout<<endl<<endl;

  cout<<"BREADTH_ORDER_MAP:"<<endl;
  cout<<"Expected: 0->1->2->3->4->5->"<<endl;
  cout<<"BreadthMap: ";
  btLnk.BreadthMap(
    [](int& dat){
      cout<<dat<<"->";
    }
  );
  lasd::BTBreadthIterator<int> itrBreadth(btLnk);
  cout<<"\nBreadthOrderIterator: ";
  while(!(itrBreadth.Terminated())){
    cout<<*itrBreadth<<"->";
    ++itrBreadth;
  }
  cout<<endl<<endl;

  lasd::SortableVector<int> vec(RandomNumber(gen) + 1);
  for(ulong i = 0; i < vec.Size(); i++) {
    vec[i] = RandomNumber(gen);
  }
  vec.Sort();
  lasd::BinaryTreeVec<int> btvec1(vec);
  lasd::BTBreadthIterator<int> breadthIterVec(btvec1);
  int next = 0;
  while(!breadthIterVec.Terminated()){
    int previous = *breadthIterVec;
    if(!(++breadthIterVec).Terminated()){
      next = *breadthIterVec;
    }
    if(previous <= next) {
      testIteratori &= true;
    } else {
      cout<<lines++<<" BTBredthIterator NON costruito correttamente da BTVec! ERROR"<<endl;
      testIteratori &= false;
      break;
    }
  }
  if(testIteratori == true) {
    cout<<lines++<<" BTBredthIterator costruito correttamente da BTVec!"<<endl;    
  }
  breadthIterVec.Reset();
  if(*breadthIterVec == vec[0]) {
    cout<<lines++<<" Iteratore resettato correttamente!"<<endl;
  } else {
    cout<<lines++<<" Iteratore NON resettato correttamente!"<<endl;
    testIteratori &= false;
  }
  lasd::BinaryTreeLnk<int> btlnk1;
  lasd::BTInOrderIterator<int> postOrderBSTlnk(btlnk1);
  if(postOrderBSTlnk.Terminated()) {
    cout<<lines++<<" Iterator is terminated: Correct!"<<endl;
  } else {
    cout<<lines++<<"Iterator is not terminated: Error!"<<endl;
    testIteratori &= false;
  }
  lasd::BTInOrderIterator<int> postOrderBSTmovelnk(std::move(btlnk));
  if(postOrderBSTlnk.Terminated()) {
    cout<<lines++<<" Iterator is terminated: Correct!"<<endl;
  } else {
    cout<<lines++<<" Iterator is not terminated: Error!"<<endl;
    testIteratori &= false;
  }

  return testIteratori;
}

//********************************************************************************
//BST

bool TestBST() {
  bool testBST = true;

  return testBST;
}
//*******************************************************************************
/* ************************************************************************** */

void mytest1() {
cout << endl <<"******** Begin of 1 test *******\n" << endl;
cout << endl <<"******** Begin of Copy and Move assignment *******\n" << endl;

cout  << "Vector = Vector: " <<((CopyAssignmentVec()) ? "Corretto" : "Errore!")<< endl;
cout  << "Vector = Vector: " <<((MoveAssignmentVec()) ? "Corretto" : "Errore!")<< endl;
cout  << "List = List: " <<((CopyAssignmentList()) ? "Corretto" : "Errore!")<< endl;
cout  << "List = List: " <<((MoveAssignmentList()) ? "Corretto" : "Errore!")<< endl;
cout  << "QueueVec = QueueVec: " <<((CopyAssignmentQueueVec()) ? "Corretto" : "Errore!")<< endl;
cout  << "QueueVec = QueueVec: " <<((MoveAssignmentQueueVec()) ? "Corretto" : "Errore!")<< endl;
cout  << "QueueList = QueueList: " <<((CopyAssignmentQueueList()) ? "Corretto" : "Errore!")<< endl;
cout  << "QueueList = QueueList: " <<((MoveAssignmentQueueList()) ? "Corretto" : "Errore!")<< endl;
cout  << "StackVec = StackVec: " <<((CopyAssignmentStackVec()) ? "Corretto" : "Errore!")<< endl;
cout  << "StackVec = StackVec: " <<((MoveAssignmentStackVec()) ? "Corretto" : "Errore!")<< endl;
cout  << "StackList = StackList: " <<((CopyAssignmentStackList()) ? "Corretto" : "Errore!")<< endl;
cout  << "StackList = StackList: " <<((MoveAssignmentStackList()) ? "Corretto" : "Errore!")<< endl;

//************

cout << endl <<"******** Begin of test Constructor **********" << endl;

cout<<"\nCOPY CONSTRUCTORS: "<<endl;
cout<<"Vector(Vector): "<<((CopyConstructorVec()) ? "Corretto" : "Errore")<<endl;
cout<<"List(List): "<<((CopyConstructorList()) ? "Corretto" : "Errore")<<endl;
cout<<"StackVec(StackVec): "<<((CopyConstructorStackVec()) ? "Corretto" : "Errore")<<endl;
cout<<"StackLst(StackList): "<<((CopyConstructorStackLst()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueLst(QueueList): "<<((CopyConstructorQueueLst()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueVec(QueueVec): "<<((CopyConstructorQueueVec()) ? "Corretto" : "Errore")<<endl;

cout<<"\nList(Vector): "<<((CopyConstructorListVec()) ? "Corretto" : "Errore")<<endl;
cout<<"Vector(List): "<<((CopyConstructorVecList()) ? "Corretto" : "Errore")<<endl;
cout<<"StackVec(Vector): "<<((CopyConstructorStackVecVec()) ? "Corretto" : "Errore")<<endl;
cout<<"StackLst(Vector): "<<((CopyConstructorStackLstVec()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueLst(vector): "<<((CopyConstructorQueueLstVec()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueVec(Vector): "<<((CopyConstructorQueueVecVec()) ? "Corretto" : "Errore")<<endl;
cout<<"StackVec(List): "<<((CopyConstructorStackVecList()) ? "Corretto" : "Errore")<<endl;
cout<<"StackLst(List): "<<((CopyConstructorStackLstList()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueLst(List): "<<((CopyConstructorQueueLstList()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueVec(List): "<<((CopyConstructorQueueVecList()) ? "Corretto" : "Errore")<<endl;


cout<<"\nMOVE CONSTRUCTORS: "<<endl;
cout<<"Vector(move(Vector)): "<<((MoveConstructorVec()) ? "Corretto" : "Errore")<<endl;
cout<<"List(move(List)): "<<((MoveConstructorList()) ? "Corretto" : "Errore")<<endl;
cout<<"StackVec(move(StackVec)): "<<((MoveConstructorStackVec()) ? "Corretto" : "Errore")<<endl;
cout<<"StackLst(move(StackList)): "<<((MoveConstructorStackLst()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueLst(move(QueueList)): "<<((MoveConstructorQueueLst()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueVec(move(QueueVec)): "<<((MoveConstructorQueueVec()) ? "Corretto" : "Errore")<<endl;


cout<<"\nList(move(Vector)): "<<((MoveConstructorLstVec()) ? "Corretto" : "Errore")<<endl;
cout<<"Vector(move(List)): "<<((MoveConstructorVecLst()) ? "Corretto" : "Errore")<<endl;
cout<<"StackVec(move(Vector)): "<<((MoveConstructorStackVecVec()) ? "Corretto" : "Errore")<<endl;
cout<<"StackLst(move(Vector)): "<<((MoveConstructorStackLstVec()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueLst(move(Vector)): "<<((MoveConstructorQueueLstVec()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueVec(move(Vector)): "<<((MoveConstructorQueueVecVec()) ? "Corretto" : "Errore")<<endl;
cout<<"StackVec(move(List)): "<<((MoveConstructorStackVecLst()) ? "Corretto" : "Errore")<<endl;
cout<<"StackLst(move(List)): "<<((MoveConstructorStackLstLst()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueLst(move(List)): "<<((MoveConstructorQueueLstLst()) ? "Corretto" : "Errore")<<endl;
cout<<"QueueVec(move(List)): "<<((MoveConstructorQueueVecLst()) ? "Corretto" : "Errore")<<endl;

//**********

cout << endl <<"******** Test List *******\n" << endl;

cout<<"Remove form an empty list: "<<endl;
cout<<"InsertAtFront: "<<((InsertAtFront())? "Corretto" : "Errore")<<endl;
cout<<"InsertAtBack: "<<((InsertAtBack())? "Corretto" : "Errore")<<endl;
cout<<"RemoveFromFronrt: "<<((RemoveFromFront())? "Corretto" : "Errore")<<endl;
cout<<"RemoveSpecificElement: "<<((RemoveSpecificElement())? "Corretto" : "Errore")<<endl;
cout<<"SwapLists: "<<((SwapLists())? "Corretto" : "Errore")<<endl;

}

/* *************************************************************************************************** */
/* *************************************************************************************************** */

void mytest2() {

cout << endl <<"********** Begin of 2 test ****************\n" << endl;

cout << endl <<"******** Begin of Iterator test *******\n" << endl;
cout<<" Test su iteratori:"<<((TestIteratori()) ? "\nTest su iteratori Corretto" : "\nErrore Test Iteratori")<<endl;

cout << endl <<"******** Begin of BST test *******\n" << endl;
cout<<" Test su BST:"<<((TestBST()) ? "\nTest su BST Corretto" : "\nErrore in Test BST")<<endl;

}

/* ************************************************************************** */

#endif