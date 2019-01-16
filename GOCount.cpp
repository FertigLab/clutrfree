#include <iostream>
#include <string>

class GOCount {

    private vector<Ontology> ontologyList;
    private int onListSize; // Size of vectors below, number of ontologies
    private vector<vector<int>> onIndexes;
    private int nGenes;
    private vector<int> valuesBin;
    private vector<Color> colors;

    /*
     *
     *                         #GO_i in Pattern_j /# Annoted genes in Pattern_j
     * counts(GO_i, pattern_j)  = --------------------------------------------
     *                      #GO_i in experiment / # Annoted Genes in experiment
     */

    private vector<int> expCountGo;    // # of go_i in total experiment
    private int expTotalGo;      // total # of go in total experiment (sum over totalCountOn)
    private vector<int> patCountGo;    // # of GO_i in current pattern
    private int patTotalGo;      // total # of GO in current pattern/cluster

    private vector<float> countOn;     // final result of enhancement
    private vector<float> pval;        // p-values from hypergeometric test

    private vector<int> onLevels;      // ontology levels

    private int totalGenesAnnoted; // total number of annoted genes in data
    private int nGenesAnnotatedCluster; // total number of genes present in cluster and annoted


    // Constructor
    public GOCount(GOData listGO) {
    	int index;
    	this->ontologyList = listGO.getOntologyList();
    	//System.out.println("\n\nOntolist = " + ontologyList);

    	this->onIndexes = listGO.getOnIndexes();

    	this->nGenes = onIndexes.size();            // # rows of the table

    	this->totalGenesAnnoted = listGO.getTotalGenesAnnoted();

    	this->onListSize = ontologyList.size();

    	// get an ontology histogram in the full experiment
    	this->expCountGo = listGO.getOnCounts();

    	//get the total number of ontological terms in the data
    	this->expTotalGo = listGO.getTotalOnCounts();

        this->onLevels = listGO.getLevels();

    	// get each color for display

    	this->colors = new Color[onListSize];

    	for (unsigned i = 0; i < onListSize; ++i) {
    	    colors[i] = ontologyList[i].getColor();
    	}
    }
}
