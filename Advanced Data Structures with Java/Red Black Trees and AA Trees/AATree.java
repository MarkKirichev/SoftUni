import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

class AATree<T extends Comparable<T>> {
    private Node<T> root;

    public static class Node<T> {
        private T element;
        private Node<T> left;
        private Node<T> right;
        private int count;
        private int level;

        public Node(T element) {
            this.element = element;
            this.count = 1;
            this.level = 1;
        }
    }

    public AATree() {
    }

    public boolean isEmpty() {
        return this.root == null;
    }

    public void clear() {
        this.root = null;
    }

    public void insert(T element) {
        if (element == null) {
            throw new IllegalArgumentException("Cannot insert null element!");
        }
        if (this.root == null) {
            this.root = new Node<>(element);
        }
        this.root = this.insertInto(this.root, element);
    }

    private Node<T> insertInto(Node<T> node, T element) {
        if (node == null) {
            return new Node<>(element);
        }
        int cmp = element.compareTo(node.element);
        if (cmp < 0) {
            node.left = insertInto(node.left, element);
        }
        if (cmp > 0) {
            node.right = insertInto(node.right, element);
        }
        if (cmp == 0) {
            return node;
        }
        if (node.left != null && areRightHorizontalLinks(node, node.left)) {
            node = skew(node);
        }
        if (node.right != null && node.right.right != null && areRightHorizontalLinks(node, node.right, node.right.right)) {
            node = split(node);
        }
        if (node.right!=null && node.left!=null && areRightHorizontalLinks(node, node.right, node.left)) {
            node.level++;
        }

        node.count = countNode(node.left) + countNode(node.right) + 1;
        return node;
    }

    @SafeVarargs
    private boolean areRightHorizontalLinks(Node<T>... nodes) {
        int level = nodes[0].level;
        for (Node<T> node : nodes) {
            if (node.level != level) {
                return false;
            }
        }
        return true;
    }

    private Node<T> split(Node<T> node) {
        Node<T> tmp = node.right;
        node.right = tmp.left;
        tmp.left = node;
        tmp.count = node.count;
        node.count = countNode(node.left) + countNode(node.right) + 1;
        tmp.level++;
        return tmp;
    }

    private Node<T> skew(Node<T> node) {
        Node<T> tmp = node.left;
        node.left = tmp.right;
        tmp.right = node;
        tmp.count = node.count;
        node.count = countNode(node.left) + countNode(node.right) + 1;
        return tmp;
    }

    public int countNodes() {
        return countNode(this.root);
    }

    private int countNode(Node<T> node) {
        if (node == null) {
            return 0;
        }
        return node.count;
    }

    public boolean search(T element) {
        List<T> elements = new ArrayList<>();
        this.inOrder(elements::add);
        return elements.contains(element);
    }

    public void inOrder(Consumer<T> consumer) {
        this.root = this.inOrderTraversal(this.root, consumer);

    }

    private Node<T> inOrderTraversal(Node<T> node, Consumer<T> consumer) {
        if (node == null) {
            return null;
        }
        if (node.left != null) {
            node.left = inOrderTraversal(node.left, consumer);
        }
        consumer.accept(node.element);
        if (node.right != null) {
            node.right = inOrderTraversal(node.right, consumer);
        }
        return node;
    }

    public void preOrder(Consumer<T> consumer) {
        this.root = this.preOrderTraversal(this.root, consumer);
    }

    private Node<T> preOrderTraversal(Node<T> node, Consumer<T> consumer) {
        if (node == null) {
            return null;
        }
        consumer.accept(node.element);
        if (node.left != null) {
            node.left = preOrderTraversal(node.left, consumer);
        }
        if (node.right != null) {
            node.right = preOrderTraversal(node.right, consumer);
        }
        return node;
    }

    public void postOrder(Consumer<T> consumer) {
        postOrderTraversal(this.root, consumer);
    }

    private Node<T> postOrderTraversal(Node<T> node, Consumer<T> consumer) {
        if (node == null) {
            return null;
        }
        if (node.left != null) {
            node.left = postOrderTraversal(node.left, consumer);
        }
        if (node.right != null) {
            node.right = postOrderTraversal(node.right, consumer);
        }
        consumer.accept(node.element);
        return node;
    }
}