#include <array>
#include <memory>
#include <string>
#include <vector>
class TreeNode
{
  public:
    bool endOfWord;
    std::array<std::shared_ptr<TreeNode>, 26> children;
    TreeNode();
};
class WordTree
{
  public:
    std::size_t mysize;
    TreeNode* root;
    WordTree();
    void add(std::string word);
    bool find(std::string word);
    std::vector<std::string> predict(std::string partial, std::uint8_t howMany);
    std::size_t size();
};