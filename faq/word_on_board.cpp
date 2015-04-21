/* Find all valid words on a board, based on:
 * http://www.mitbbs.com/article_t/JobHunting/31757463.html
 * The code has some compiling errors, but the idea seems clear.
 */

#include <string>
#include <set>
#include <deque>

using namespace std;

class CTryNode;

class CTry {
public:
  CTryNode* Advance(CTryNode* pNode, char ch);
  CTryNode* Back(CTryNode* pNode);
  string GetValue(CTryNode* pNode);
  bool IsCurrValueAWord(CTryNode* pNode);

  static CTry* GetTryPtr();
};

class CCell {
  friend class CBoard;
public:
  char GetVal();

private:
  int m_nRowIdx;
  int m_nColIdx;
  char m_chVal;

};

class CBoard {
public:
  CCell* GetCellPtr(int i, int j);
  void AddWordsOrignAtOneCell(set<string> setWords, CCell* pCell);
  void AddWordsHelper(set<string>& setWords, CCell* pCell,deque<CCell*>& dequeCell,CTryNode *pTryNode);   
  set<string> GetAllWordsOnBoard();
  bool IsCellInCellDeque(CCell* pCell, deque<CCell*> dequeCell);

private:
  void SetNeighbourCellsForCell(int i, int j);
  void SetNeighbourCellsForCell(CCell pCell);

  CTry* pTry;
  int m_nRowNum;
  int m_nColNum;
  CCell*** m_pppCell;
  CCell* m_aNeighbourCellPtr[8];
};

void CBoard::AddWordsHelper(set<string>& setWords, CCell* pCell, deque<CCell*>& dequeCell, CTryNode *pTryNode) {
  if(!pCell)
    return;
   
  // -- Check whether it is in the current Cell Path
  if(this->IsCellInCellDeque(pCell,dequeCell))
    return;
       
  // -- Advance in Try
  CTryNode* pNextTryNode = pTry->Advance(pTryNode,pCell->GetVal());
  if(!pNextTryNode)
    return;
   
  dequeCell.push_back(pCell);
   
  // -- add the word to the output if it is a word
  if ( pTry->IsCurrValueAWord(pNextTryNode) && setWords.find(pTry->GetValue(pNextTryNode)) == setWords.end() )
    setWords.insert(pTry->GetValue(pNextTryNode));
   
  this->SetNeighbourCellsForCell(pCell);
  CCell* pCurrNeighbour = NULL;
  for (int i = 0; i < 8; i++) {
    pCurrNeighbour = this->m_aNeighbourCellPtr[i];       
    AddWordsHelper(setWords, pCurrNeighbour, dequeCell, pNextTryNode);
  }   
   
  dequeCell.pop_end(pCell);
}

void CBoard::AddWordsOrignAtOneCell(set<string>& setWords& setWords, CCell* pCell) {
  if(!pCell)
    return;

  deque<CCell*> dequeCell;
  CTryNode* pTryNode=null;
  this->AddWordsHelper(setWords, pCell, dequeCell, pTryNode);
}

set<string> CBoard::GetAllWordsOnBoard() {
  this->pTry = CTry::GetTryPtr();
  CCell* pCell = null;
  set<string> setWords;
  for(int i = 0; i  <this->m_nRowNum; i++) {
    for(int j = 0; j  this->m_nColNum; j++) {
      pCell = this->m_pppCell[i][j];
      this->AddWordsOrignAtOneCell(setWords,pCell);
    }
  }

  return setWords;
}
