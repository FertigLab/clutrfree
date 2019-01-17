#include <iostream>
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
    vector<float> getValues() {
        return values;
    }

    vector<float> getUncertainties() {
	    return sigma;
    }

    vector<int> getValuesBin() {
	    return valuesBin;
    }

    vector<vector<float>> getPatternMatrix() {
	    return patternMatrix;
    }

    float getMaxPattern() {
	    return patternMax;
    }

    vector<vector<float>> getPatSigmaMatrix() {
	    return patSigmaMatrix;
    }

    vector<vector<float>> getAmpliMatrix() {
	    return ampliMatrix;
    }

    float getMaxAmplitude() {
	    return this.amplitudeMax;
    }

    vector<vector<float>> getAmpSigmaMatrix() {
	    return ampliSigmaMatrix;
    }

    void setPersistenceMatrix(vector<vector<int>> pers) {
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

    void clearPersistence() {
    	for(unsigned i = 0; i < valuesBin.size(); ++i) {
    	    persistence[i] = valuesBin[i];
    	}
    }

    vector<vector<int>> getPersistenceMatrix() {
	    return persistenceMatrix;
    }

    int getMaxPersistence() {
	    return persistenceMax;
    }

    void setPersistence(vector<int> persistence) {
	    this->persistence = persistence;
    }

    vector<int> getPersistence() {
	    return persistence;
    }

    void print() {
    	for (unsigned i = 0; i < values.length; ++i) {
    	    cout << i << ":" << values[i] << "(" << sigma[i] << endl;
    	}
    }

    /**
     * Update the cutoff and valuesBin variables...
     * Reset the persistence....
     * Update the gene annot count;
     */
    void setCutoff(float cutoff) {
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
    Vector<CountValue> getCount() {
	    return countOn;
    }

    GOCount getGC() {
	    return gc;
    }

    /**
     * set the full count matrix and p-values matrix
     */
    void setCountMatrix(vector<vector<CountValue>> countMatrix) {
	    this->countMatrix = countMatrix;
    }

    /**
     * get the on count matrix
     */
    vector<vector<CountValue>> getCountMatrix() {
	    return countMatrix;
    }

    /**
     * get the number of elements > cutoff
     */
    int getNvalues() {
	    return nvalues;
    }
}
