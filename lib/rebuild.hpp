#ifndef REBUILD_HPP
#define REBUILD_HPP
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
template<typename ValType>
struct TreeNode {
    using node_val = ValType;
    using node_ptr = std::shared_ptr<TreeNode<node_val>>;
    ValType val;
    node_ptr left;
    node_ptr right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {
    }
    explicit TreeNode(node_val x) : val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(node_val x, node_ptr left, node_ptr right)
        : val(x), left(std::move(left)), right(std::move(right)) {
    }
};


template<typename ValType>
typename TreeNode<ValType>::node_ptr rebuild_by_postorder_recursive(
        std::vector<ValType> postorder,
        std::vector<ValType> middle_order) {
    if (postorder.empty() || middle_order.empty()) {
        return nullptr;
    }
    auto root = std::make_shared<TreeNode<ValType>>(postorder.back());
    std::size_t root_idx = -1;
    for (std::size_t i = 0; i < middle_order.size(); ++i) {
        if (middle_order.at(i) == postorder.back()) {
            root_idx = i;
            break;
        }
    }
    if (root_idx == -1) {
        throw std::runtime_error("rebuild error!");
    }
    root->left = rebuild_by_postorder_recursive(
            std::vector<ValType>(
                    postorder.begin(),
                    postorder.begin() + root_idx),
            std::vector<ValType>(
                    middle_order.begin(),
                    middle_order.begin() + root_idx));
    root->right = rebuild_by_postorder_recursive(
            std::vector<ValType>(
                    postorder.begin() + root_idx,
                    postorder.end() - 1),
            std::vector<ValType>(
                    middle_order.begin() + root_idx + 1,
                    middle_order.end()));
    return root;
}
void test() {
    auto res = rebuild_by_postorder_recursive<int>(
            {4, 2, 7, 5, 6, 3, 1},
            {2, 4, 1, 5, 7, 3, 6});
}
#endif