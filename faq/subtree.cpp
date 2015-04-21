// is tree2 a sub-tree of tree1?
bool HasSubtree(TreeNode* pTreeHead1, TreeNode* pTreeHead2)
{
  if((pTreeHead1 == NULL && pTreeHead2 != NULL) ||
     (pTreeHead1 != NULL && pTreeHead2 == NULL))
    return false;
  
  if(pTreeHead1 == NULL && pTreeHead2 == NULL)
    return true;
  
  return HasSubtreeCore(pTreeHead1, pTreeHead2);
}

bool HasSubtreeCore(TreeNode* pTreeHead1, TreeNode* pTreeHead2)
{
  bool result = false;
  if (pTreeHead1->m_nValue == pTreeHead2->m_nValue)
    result = DoesTree1HaveAllNodesOfTree2(pTreeHead1, pTreeHead2);

 
  if (!result && pTreeHead1->m_pLeft != NULL)
    result = HasSubtreeCore(pTreeHead1->m_pLeft, pTreeHead2);
 
  if (!result && pTreeHead1->m_pRight != NULL)
    result = HasSubtreeCore(pTreeHead1->m_pRight, pTreeHead2);
 
  return result;
}

bool DoesTree1HaveAllNodesOfTree2(TreeNode* pTreeHead1, TreeNode* pTreeHead2)
{
  if (pTreeHead2 == NULL)
    return true;
 
  if (pTreeHead1 == NULL)
    return false;
  
  if (pTreeHead1->m_nValue != pTreeHead2->m_nValue)
    return false;
 
  return DoesTree1HaveAllNodesOfTree2(pTreeHead1->m_pLeft, pTreeHead2->m_pLeft) &&
    DoesTree1HaveAllNodesOfTree2(pTreeHead1->m_pRight, pTreeHead2->m_pRight);
}
 
