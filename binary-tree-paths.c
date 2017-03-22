int pathsNum (struct TreeNode* root);
void Traverse (struct TreeNode* root, char** array, char* spre, int* pindex);
char* stringAdd (char* s, int val);

char** binaryTreePaths(struct TreeNode* root, int* returnSize) {
  int index = 0;
  if (root == NULL)  return NULL;
  int paths = *returnSize = pathsNum(root);
  char** pathsArray = (char**) calloc (paths, sizeof (char*));
  Traverse (root, pathsArray, "", &index);
  return pathsArray;
}

int pathsNum (struct TreeNode* root)
{
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->right == NULL)
    return 1;
  return pathsNum(root->left) + pathsNum(root->right);
}

void Traverse (struct TreeNode* root, char** array, char* spre, int* pindex)
{
  char* s;
  if (root->left == NULL && root->right == NULL)
  {
    s = stringAdd (spre, root->val);
    array[(*pindex)++] = s;
  }
  if (root->left != NULL)
  {
    s = stringAdd (spre, root->val);
    Traverse (root->left, array, s, pindex);
    free (s);
  }
  if (root->right != NULL)
  {
    s = stringAdd (spre, root->val);
    Traverse (root->right, array, s, pindex);
    free (s);
  }
}

char* stringAdd (char* s, int val)
{
  char temp[10];
  if (s == "")
    sprintf (temp,"%d", val);
  else
    sprintf (temp, "->%d", val);
  char* snew = (char*) calloc (strlen (s) + strlen (temp) + 1, sizeof (char));
  strcpy (snew, s);
  strcat (snew, temp);
  return snew;
}

