#include <string>
#include <vector>

using namespace std;

class Pattern {
    // Attributes
    private vector<float> values;         // the "profile" contained in a pattern
    private vector<float> sigma;          // Uncertainties of the profile
    private vector<int> valuesBin;        // values verifying value[i]>cutoff*sigma[i];
    private int nvalues;                // # of values set to 1
    private vector<int> persistence;          // # persistence of the values(son-father)
    private float cutoff;               // cutoff to binarize the data

    private vector<vector<float>> patternMatrix;    // corresponding full pattern matrix
    private vector<vector<float>> patSigmaMatrix;   // corresponding full pattern uncertainties
    private vector<vector<float>> ampliMatrix;      // corresponding full amplitude matrix
    private vector<vector<float>> ampliSigmaMatrix;  // corresponding full amplitude uncertainties

    private vector<vector<int>> persistenceMatrix;   // corresponding full persistence matrix

    private int persistenceMax;          // max of persistenceMatrix
    private float amplitudeMax;          // max of ampliMatrix

    private float patternMax;

    /*
    private GOCount gc;                  // gene GO count
    private int[] valuesCountBin;        // values from wich to count the ontologies
    private float[] sigmaCount;
    private float[] valuesCount;
    private CountValue[] countOn;               // normalized ontological counts and p values


    private CountValue[][] countMatrix;       // full count matrix
    */

    // Constructor
    //public Pattern(float[] values, float[] sigma, float cutoff, float[][] pat, float[][] sgp, float[][] amp, float[][] sga, GOData geneGO, int index)
    public Pattern(vector<float> values, vector<float> sigma, float cutoff, vector<vector<float>> pat, vector<vector<float>> sgp, vector<vector<float>> amp, vector<vector<float>> sga, int index): values(values), sigma(sigma), cutoff(cutoff), patternMatrix(pat), patSigmaMatrix(sgp), ampliMatrix(amp), ampliSigmaMatrix(sga)
    {
        int i,j;
        valuesBin = vector<int>(this->values.size());
        persistence = vector<int>(this->values.size());

        if (geneGO != NULL && geneGO.getOnIndexes() != NULL) {
            gc = new GOCount(geneGO);

            valuesCountBin = vector<int>(this->amp.size());

            valuesCount = vector<float>(this->amp.size());
            sigmaCount = vector<float>(this->amp.size());

            for (unsigned i = 0; i < valuesCount.size(); ++i) {
                valuesCount[i] = amp[i][index];
                sigmaCount[i] = sga[i][index];
            }
        } else gc = NULL;

        setCutoff(cutoff);
        for (unsigned i = 0; i < valuesBin.size(); ++i) {
            persistence[i] = valuesBin[i];
        }

        int height = this->amp.size();
        int width = this->amp[0].size();
        float max = this->amp[0][0];

        for (unsigned i = 0; i < height; ++i) {
            for (unsigned j = 0; j < width; ++j) {
                if (amp[i][j] > max) max = pat[i][j];
            }
        }
        patternMax = max;
    }



    // Operations
    public vector<float> getValues() {
        return values;
    }

    public vector<float> getUncertainties() {
	    return sigma;
    }

    public vector<int> getValuesBin() {
	    return valuesBin;
    }

    public vector<vector<float>> getPatternMatrix() {
	    return patternMatrix;
    }

    public float getMaxPattern() {
	    return patternMax;
    }

    public vector<vector<float>> getPatSigmaMatrix() {
	    return patSigmaMatrix;
    }

    public vector<vector<float>> getAmpliMatrix() {
	    return ampliMatrix;
    }

    public float getMaxAmplitude() {
	    return this.amplitudeMax;
    }

    public vector<vector<float>> getAmpSigmaMatrix() {
	    return ampliSigmaMatrix;
    }

    public void setPersistenceMatrix(vector<vector<int>> pers) {
    	persistenceMatrix = pers;

    	int height = pers.size();
    	int width = pers[0].size();
    	int max = 0;
    	for(unsigned i = 0; i < height; ++i) {
    	    for(unsigned j = 0; j < width; ++j) {
                if(pers[i][j] > max) max = pers[i][j];
    	    }
    	}
    	persistenceMax = max;
    }

    public void clearPersistence() {
    	for(unsigned i = 0; i < valuesBin.size(); ++i) {
    	    persistence[i] = valuesBin[i];
    	}
    }

    public vector<vector<int>> getPersistenceMatrix() {
	    return persistenceMatrix;
    }

    public int getMaxPersistence() {
	    return persistenceMax;
    }

    public void setPersistence(vector<int> persistence) {
	    this->persistence = persistence;
    }

    public vector<int> getPersistence() {
	    return persistence;
    }

    public void print() {
    	for (unsigned i = 0; i < values.length; ++i) {
    	    cout << i << ":" << values[i] << "(" << sigma[i] << endl;
    	}
    }

    /**
     * Update the cutoff and valuesBin variables...
     * Reset the persistence....
     * Update the gene annot count;
     */
    public void setCutoff(float cutoff) {
    	this->cutoff = cutoff;

    	//System.out.println("reset cutoff and persistence");
    	nvalues = 0;

    	for (unsigned i = 0; i < values.size(); ++i) {
    	    if(values[i] > cutoff * sigma[i]) {
                valuesBin[i] = 1;
                nvalues++;
    	    } else valuesBin[i] = 0;
    	    persistence[i] = valuesBin[i];
	    }


    	// Update GO Counts

    	if(gc != NULL) {
    	    for (unsigned i = 0; i < values.size(); ++i) {
        		if(valuesCount[i] > cutoff * sigmaCount[i]) {
        		    valuesCountBin[i] = 1;
        		} else valuesCountBin[i] = 0;
    	    }
    	    countOn = gc.countGo(valuesCountBin);
    	} else countOn = NULL;
    }



    /**
     * return the go counts
     */
    public CountValue[] getCount() {
	    return countOn;
    }

    public GOCount getGC() {
	    return gc;
    }

    /**
     * set the full count matrix and p-values matrix
     */
    public void setCountMatrix(vector<vector<CountValue>> countMatrix) {
	    this->countMatrix = countMatrix;
    }

    /**
     * get the on count matrix
     */
    public vector<vector<CountValue>> getCountMatrix() {
	    return countMatrix;
    }

    /**
     * get the number of elements > cutoff
     */
    public int getNvalues() {
	    return nvalues;
    }
}
