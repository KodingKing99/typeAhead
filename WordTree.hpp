#include <array>
#include <memory>
#include <string>
#include <vector>
class TreeNode
{
  public:
    bool endOfWord;
    std::array<std::shared_ptr<TreeNode>, 26> children;
    std::string nodename;
    TreeNode();
    TreeNode(std::string name);
    void setnodename(std::string name);
};
class WordTree
{
  public:
    std::size_t mysize;
    std::shared_ptr<TreeNode> root;
    WordTree();
    void add(std::string word);
    bool find(std::string word);
    void toString(std::shared_ptr<TreeNode> node);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size();

  private:
    bool findRecursive(std::string word, std::shared_ptr<TreeNode> currNode, int i);
    std::shared_ptr<TreeNode> getMyNode(std::string partial, std::shared_ptr<TreeNode> currNode, int i);
};