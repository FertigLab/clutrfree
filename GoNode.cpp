      class GONode {
      public:
 
      // Constants

      private static int MAXSons = 10;

      // Attributes

      public GONode parent;    // up and down pointers
      public vector<GONode> son;
      public int nsons;

      public GONode prev;   // left and right pointers between sons
      public GONode next;

      public int level;    // hierarchical level

      public float xpos;   // x and y plot position
      public float ypos;

      public Ontology content;

      // Constructors
      public GONode(GONode next, GONode prev, GONode up, GONode down, Ontology content, int level) {

        this->prev = prev;
        this->next = next;

        this->parent = parent;

        this->content = content;
        this->level = level;

        this->son = new GONode[MAXSons];
        this->nsons = 0;
      }

      // Operations

      /*public void printAttributes() {
        content.print();
      }
      */
  }
