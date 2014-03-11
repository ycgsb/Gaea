#ifndef RECSYSEXPERIMENT_H
#define RECSYSEXPERIMENT_H

namespace ycg {

template<class Loader, class LoaderConfig, class Data, class Model, class ModelConfig, class Evaluator, class EvaluatorConfig>
class RecSysExperiment {
public:
	RecSysExperiment(const LoaderConfig& ldcfg, const ModelConfig& mdcfg, const EvaluatorConfig& evalcfg) :
		_ldcfg(ldcfg), _mdcfg(mdcfg), _evalcfg(evalcfg) { }
	virtual ~RecSysExperiment() { };
	void perform();
private:
	const LoaderConfig& _ldcfg;
	const ModelConfig& _mdcfg;
	const EvaluatorConfig& _evalcfg;
};

template<class Loader, class LoaderConfig, class Data, class Model, class ModelConfig, class Evaluator, class EvaluatorConfig>
void RecSysExperiment<Loader, LoaderConfig, Data, Model, ModelConfig, Evaluator, EvaluatorConfig>::perform() {
	Loader loader(_ldcfg);
	Data trainData = loader.readTrainData();
	Model model(trainData, _mdcfg);
	model.train();
	Data testData = loader.readTestData();
	Evaluator evaluator(model, testData, _evalcfg);
	evaluator.evaluate();
}

} //~ namespace ycg

#endif /* RECSYSEXPERIMENT_H */
