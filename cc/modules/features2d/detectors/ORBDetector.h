#include "macros.h"
#include "../FeatureDetector.h"

#ifndef __FF_ORBDETECTOR_H__
#define __FF_ORBDETECTOR_H__

class ORBDetector : public FeatureDetector {
public:
	cv::Ptr<cv::ORB> detector;

  static NAN_MODULE_INIT(Init); 
  static NAN_METHOD(New);

	static FF_GETTER(ORBDetector, GetNFeatures, detector->getMaxFeatures());
	static FF_GETTER(ORBDetector, GetScaleFactor, detector->getScaleFactor());
	static FF_GETTER(ORBDetector, GetNlevels, detector->getNLevels());
	static FF_GETTER(ORBDetector, GetEdgeThreshold, detector->getEdgeThreshold());
	static FF_GETTER(ORBDetector, GetFirstLevel, detector->getFirstLevel());
	static FF_GETTER(ORBDetector, GetWTA_K, detector->getWTA_K());
	static FF_GETTER(ORBDetector, GetScoreType, detector->getScoreType());
	static FF_GETTER(ORBDetector, GetPatchSize, detector->getPatchSize());
	static FF_GETTER(ORBDetector, GetFastThreshold, detector->getFastThreshold());

  static Nan::Persistent<v8::FunctionTemplate> constructor;

	cv::Ptr<cv::FeatureDetector> getDetector() {
		return detector;
	}

	struct NewWorker : CatchCvExceptionWorker {
	public:
		int nfeatures = 500;
		double scaleFactor = 1.2f;
		int nlevels = 8;
		int edgeThreshold = 31;
		int firstLevel = 0;
		int WTA_K = 2;
		int scoreType = cv::ORB::HARRIS_SCORE;
		int patchSize = 31;
		int fastThreshold = 20;

		bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
			return (
				FF::IntConverter::optArg(0, &nfeatures, info) ||
				FF::DoubleConverter::optArg(1, &scaleFactor, info) ||
				FF::IntConverter::optArg(2, &nlevels, info) ||
				FF::IntConverter::optArg(3, &edgeThreshold, info) ||
				FF::IntConverter::optArg(4, &firstLevel, info) ||
				FF::IntConverter::optArg(5, &WTA_K, info) ||
				FF::IntConverter::optArg(6, &scoreType, info) ||
				FF::IntConverter::optArg(7, &patchSize, info) ||
				FF::IntConverter::optArg(8, &fastThreshold, info)
				);
		}

		bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
			return FF::isArgObject(info, 0);
		}

		bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
			v8::Local<v8::Object> opts = info[0]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
			return (
				FF::IntConverter::optProp(&nfeatures, "nfeatures", opts) ||
				FF::DoubleConverter::optProp(&scaleFactor, "scaleFactor", opts) ||
				FF::IntConverter::optProp(&nlevels, "nlevels", opts) ||
				FF::IntConverter::optProp(&edgeThreshold, "edgeThreshold", opts) ||
				FF::IntConverter::optProp(&firstLevel, "firstLevel", opts) ||
				FF::IntConverter::optProp(&WTA_K, "WTA_K", opts) ||
				FF::IntConverter::optProp(&scoreType, "scoreType", opts) ||
				FF::IntConverter::optProp(&patchSize, "patchSize", opts) ||
				FF::IntConverter::optProp(&fastThreshold, "fastThreshold", opts)
				);
		}

		std::string executeCatchCvExceptionWorker() {
			return "";
		}
	};

};

#endif