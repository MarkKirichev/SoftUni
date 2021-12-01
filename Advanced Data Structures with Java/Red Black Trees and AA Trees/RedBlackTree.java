import java.util.ArrayDeque;
import java.util.Deque;
import java.util.List;

public class RedBlackTree<Key extends Comparable<Key>, Value> {

    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private Node root;     // root of the BST

    // BST helper node data type
    private class Node {
        private Key key;           // key
        private Value val;         // associated data
        private Node left, right;  // links to left and right subtrees
        private boolean color;     // color of parent link
        private int size;          // subtree count

        public Node(Key key, Value val, boolean color, int size) {
            this.key = key;
            this.val = val;
            this.color = color;
            this.size = size;
        }
    }

    public RedBlackTree() {
    }

    // is node x red; false if x is null ?
    private boolean isRed(Node x) {
        if (x == null) {
            return false;
        }
        return x.color;
    }

    // number of node in subtree rooted at x; 0 if x is null
    private int size(Node x) {
        if (x == null) {
            return 0;
        }
        return x.size;
    }


    /**
     * Returns the number of key-value pairs in this symbol table.
     *
     * @return the number of key-value pairs in this symbol table
     */
    public int size() {
        return this.size(this.root);
    }

    /**
     * Is this symbol table empty?
     *
     * @return {@code true} if this symbol table is empty and {@code false} otherwise
     */
    public boolean isEmpty() {
        return this.root == null;
    }

    public Value get(Key key) {
        return this.get(this.root, key);
    }

    // value associated with the given key in subtree rooted at x; null if no such key
    private Value get(Node x, Key key) {
        if (key == null || x == null) {
            return null;
        }
//        if (x==null){
//            throw new IllegalStateException("Attention! Empty tree");
//        }
        Node current = x;
        while (current != null) {
            int cmp = key.compareTo(current.key);
            if (cmp < 0) {
                current = current.left;
            } else if (cmp > 0) {
                current = current.right;
            } else {
                return current.val;
            }
        }
        return null;
    }

    public boolean contains(Key key) {
        return this.get(key) != null;
    }

    public void put(Key key, Value val) {
        this.root = this.put(this.root, key, val);
        this.root.color = BLACK;
    }

    // insert the key-value pair in the subtree rooted at h
    private Node put(Node h, Key key, Value val) {
        if (h == null) {
            return new Node(key, val, RED, 1);
        }

        int cmp = key.compareTo(h.key);
        if (cmp < 0) {
            h.left = this.put(h.left, key, val);
        } else if (cmp > 0) {
            h.right = this.put(h.right, key, val);
        } else {
            h.val = val;
        }

        return balance(h);
    }

    public void deleteMin() {
        if (this.isEmpty()) {
            throw new IllegalStateException("The tree is empty!");
        }
        if (this.root.left == null) {
            this.root = null;
            return;
        }
        this.deleteMin(this.root);
    }

    // delete the key-value pair with the minimum key rooted at h
//    private Node deleteMin(Node h) {
//        if (h==null){
//            return null;
//        }
//        Node current = h;
//        Node prev = current;
//        while (current.left!=null){
//            prev.size--;
//            prev = current;
//            current = current.left;
//        }
//        prev.size--;
//        prev.left = current.right;
//        return current;
//    }

    private Node deleteMin(Node h) {
        if (h.left == null) {
            return null;
        }
        if (!isRed(h.left) && !isRed(h.left.left)) {
            h = this.moveRedLeft(h);
        }

        h.left = deleteMin(h.left);
        return balance(h);
    }

    public void deleteMax() {
        if (this.isEmpty()) {
            throw new IllegalStateException("Empty tree!");
        }
        if (this.root.right == null) {
            this.root = null;
        }
        if (this.root==null){
            throw new IllegalStateException("Null root!");
        }
        this.deleteMax(this.root);
    }

    private Node deleteMax(Node h) {
        if (this.isRed(h.left)) {
            h = rotateRight(h);
        }
        if (h.right == null) {
            return null;
        }
        if (!isRed(h.right) && !isRed(h.right.left)) {
            h = moveRedRight(h);
        }
        h.right = deleteMax(h.right);
        return balance(h);
    }

    // delete the key-value pair with the maximum key rooted at h
//    private Node deleteMax(Node h) {
//        if (h==null){
//            return null;
//        }
//        Node current = h;
//        Node prev = current;
//        while (current.right!=null){
//            prev.size--;
//            prev = current;
//            current = current.right;
//        }
//        prev.size--;
//        prev.right = current.left;
//        return current;
//    }

    public void delete(Key key) {
        if (this.isEmpty() || key == null) {
            throw new IllegalStateException("Empty tree!");
        }
        if (this.root.key.compareTo(key) == 0) {
            this.root = null;
            return;
        }

        if (!contains(key)) {
            return;
        }
        this.root = this.delete(this.root, key);
        if (!this.isEmpty()) {
            this.root.color = BLACK;
        }
    }

    // delete the key-value pair with the given key rooted at h
    private Node delete(Node h, Key key) {
        if (h == null) {
            return null;
        }
        int cmp = key.compareTo(h.key);
        if (cmp < 0) {
            if (!isRed(h.left) && isRed(h.left.left)){
                h = moveRedLeft(h);
            }
            h.left = delete(h.left, key);
        } else  {
            if (isRed(h.left)){
                h = rotateRight(h);
            }
            if (cmp==0 && h.right==null){
                return null;
            }
            if (isRed(h.right) && isRed(h.right.left)){
                h = moveRedRight(h);
            }
            if (cmp==0) {
                Node min = min(h.right);
                h.key = min.key;
                h.val = min.val;
                h.right = deleteMin(h.right);
            }else {
                h.right = delete(h.right, key);
            }
        }
        return balance(h);
    }

    private Node rotateRight(Node h) {
        Node temp = h.left;
        h.left = temp.right;
        temp.right = h;
        temp.color = h.color;
        h.color = !h.color;
        temp.size = h.size;
        h.size = this.size(h.left) + this.size(h.right) + 1;
        return temp;
    }

    // make a right-leaning link lean to the left
    private Node rotateLeft(Node h) {
        Node temp = h.right;
        h.right = temp.left;
        temp.left = h;
        temp.color = h.color;
        h.color = RED;
        temp.size = h.size;
        h.size = this.size(h.left) + this.size(h.right) + 1;
        return temp;
    }

    // flip the colors of a node and its two children
    private void flipColors(Node h) {
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }

    // Assuming that h is red and both h.left and h.left.left
    // are black, make h.left or one of its children red.
    private Node moveRedLeft(Node h) {
        flipColors(h);
        if (!isRed(h.right) && !isRed(h.right.left)) {
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    // Assuming that h is red and both h.right and h.right.left
    // are black, make h.right or one of its children red.
    private Node moveRedRight(Node h) {
        flipColors(h);
        if (!isRed(h.left) && !isRed(h.left.left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    // restore red-black tree invariant
    private Node balance(Node h) {
        if (isRed(h.right) && !isRed(h.left)) {
            h = rotateLeft(h);
        }
        if (isRed(h.left) && isRed(h.left.left)) {
            h = rotateRight(h);
        }
        if (isRed(h.left) && isRed(h.right)) {
            flipColors(h);
        }
        h.size = this.size(h.left) + this.size(h.right) + 1;
        return h;
    }

    public int height() {
        return this.height(this.root);
    }

    private int height(Node x) {
        if (x == null) {
            return -1;
        }
        return Math.max(this.height(x.left), this.height(x.right)) + 1;
    }

//    private int height(Node x) {
//        if (x==null){
//            return -1;
//        }
//        int height = 0;
//        Node current = x;
//        while (current!=null){
//            if (!isRed(current)){
//                height++;
//            }
//            current = current.left;
//        }
//        return height;
//    }

    public Key min() {
        Node min = this.min(this.root);
        return min == null ? null : min.key;
    }

    // the smallest key in subtree rooted at x; null if no such key
    private Node min(Node x) {
        if (x == null) {
            return null;
        }
        Node current = x;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }

    public Key max() {
        Node max = this.max(this.root);
        return max == null ? null : max.key;
    }

    // the largest key in the subtree rooted at x; null if no such key
    private Node max(Node x) {
        if (x.right == null) {
            return x;
        }
        return max(x.right);
    }

    public Key floor(Key key) {
        Node floorNode = this.floor(this.root, key);
        return floorNode==null ? null : floorNode.key;
    }

    // the largest key in the subtree rooted at x less than or equal to the given key
    private Node floor(Node x, Key key) {
        if (x==null){
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp==0){
            return x;
        }
        if (cmp<0){
            return floor(x.left, key);
        }else {
            Node rightFloor = floor(x.right, key);
            if (rightFloor==null){
                return x;
            }
            return rightFloor;
        }
    }

    public Key ceiling(Key key) {
        Node ceilingNode = this.ceiling(this.root, key);
        return ceilingNode==null ? null : ceilingNode.key;
    }

    // the smallest key in the subtree rooted at x greater than or equal to the given key
    private Node ceiling(Node x, Key key) {
        if (x==null){
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp==0){
            return x;
        }
        if (cmp>0){
            return ceiling(x.right, key);
        }
        Node ceilingLeft = ceiling(x.left, key);
        if (ceilingLeft==null){
            return x;
        }
        return ceilingLeft;
    }

    public Key select(int rank) {
        return this.select(this.root, rank);
    }

    // Return key in BST rooted at x of given rank.
    // Precondition: rank is in legal range.
    private Key select(Node x, int rank) {
        if (x==null){
            return null;
        }

        int leftRank = size(x.left);
        if (leftRank > rank){
            return select(x.left, rank);
        }else
        if (leftRank < rank){
            return select(x.right, rank - leftRank-1);
        }else {
            return x.key;
        }
    }

    public int rank(Key key) {
        return this.rank(key, this.root);
    }

    // number of keys less than key in the subtree rooted at x
    private int rank(Key key, Node x) {
        if (x==null){
            return 0;
        }
        int cmp = key.compareTo(x.key);
        if (cmp<0){
            return this.rank(key, x.left);
        }else if (cmp>0){
            return size(x.left) + 1 + rank(key, x.right);
        }else {
            return size(x.left);
        }
    }

    public Iterable<Key> keys() {
        return this.keys(min(), max());
    }

    public Iterable<Key> keys(Key lo, Key hi) {
        Deque<Key> deque = new ArrayDeque<>();
//        if (isEmpty()){
//            throw new IllegalStateException("Empty tree!");
//        }
        if (lo==null || hi==null){
            throw new IllegalArgumentException("Null bound!");
        }
        this.keys(this.root, deque, lo, hi);
        return deque;
    }

    // add the keys between lo and hi in the subtree rooted at x
    // to the queue
    private void keys(Node x, Deque<Key> queue, Key lo, Key hi) {
        if (x==null){
            return;
        }
        int cmp1 = lo.compareTo(x.key);
        int cmp2 = hi.compareTo(x.key);
        if (cmp1<0){
            keys(x.left, queue, lo, hi);
        }
        if (cmp2>0){
            keys(x.right, queue, lo, hi);
        }
        if (cmp1<=0 && cmp2>=0){
            queue.offer(x.key);
        }
    }

    public int size(Key lo, Key hi) {
        return ((List<Key>) keys(lo, hi)).size();
    }

    private boolean check() {
        return false;
    }

    // does this binary tree satisfy symmetric order?
    // Note: this test also ensures that data structure is a binary tree since order is strict
    private boolean isBST() {
        return false;
    }

    // is the tree rooted at x a BST with all keys strictly between min and max
    // (if min or max is null, treat as empty constraint)
    private boolean isBST(Node x, Key min, Key max) {
        return false;
    }

    // are the size fields correct?
    private boolean isSizeConsistent() {
        return false;
    }

    private boolean isSizeConsistent(Node x) {
        return false;
    }

    // check that ranks are consistent
    private boolean isRankConsistent() {
        return false;
    }

    // Does the tree have no red right links, and at most one (left)
    // red links in a row on any path?
    private boolean isTwoThree() {
        return false;
    }

    private boolean isTwoThree(Node x) {
        return false;
    }

    // do all paths from root to leaf have same number of black edges?
    private boolean isBalanced() {
        return false;
    }

    // does every path from the root to a leaf have the given number of black links?
    private boolean isBalanced(Node x, int black) {
        return false;
    }
}