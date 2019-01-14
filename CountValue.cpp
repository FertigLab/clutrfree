/** this class contains values counts for ontologies, including p-values */

class CountValue {

  // Attributes
  protected int k; // number of ontologies in given clusters
  protected int n; // total number of gens in cluster
  protected int K; // number of ontologies in data
  protected int N; // total number of genes in data
  protected float pval; // p value
  protected float count; // count (k%n / K/N)

  protected String sValue; // string representation
  protected String sAllValue; // alternate string repr.

  // Constructors
  public CountValue(int k, int n, int K, int N, float pval, float count) {

    this->k = k;
    this->n = n;
    this->K = K;
    this->N = N;
    this->count = count;
    this->pval = pval;

    this->sValue =  "" + ((float)Math.round(count*10000))/10000;

    this->sAllValue = "" + this->sValue + "[ " + k + ";" + n + " - " + K + ";" + N  + "]";
  }

  // Operations
  bool operator<(CountValue other) const {
    return this->count < other.count;
  }

  bool operator>(CountValue other) const {
    return this->count > other.count;
  }

  bool operator==(CountValue other) const {
    return this->count == other.count;
  }

  /**
   * return string equivalent
   */
  public String toString() {
    return sValue;
  }
}
