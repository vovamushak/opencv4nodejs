#include "Mat.h"
#include "MatImgproc.h"
#include "MatCalib3d.h"
#include "ExternalMemTracking.h"

Nan::Persistent<v8::FunctionTemplate> Mat::constructor;

NAN_MODULE_INIT(Mat::Init) {

  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Mat::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Mat").ToLocalChecked());
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("rows").ToLocalChecked(), Mat::GetRows);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("cols").ToLocalChecked(), Mat::GetCols);
  Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("type").ToLocalChecked(), Mat::GetType);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("channels").ToLocalChecked(), Mat::GetChannels);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("dims").ToLocalChecked(), Mat::GetDims);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("depth").ToLocalChecked(), Mat::GetDepth);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("empty").ToLocalChecked(), Mat::GetIsEmpty);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("sizes").ToLocalChecked(), Mat::GetSizes);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("elemSize").ToLocalChecked(), Mat::GetElemSize);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("step").ToLocalChecked(), Mat::GetStep);

	Nan::SetMethod(ctor, "eye", Eye);
	Nan::SetPrototypeMethod(ctor, "flattenFloat", FlattenFloat);

	Nan::SetPrototypeMethod(ctor, "at", At);
	Nan::SetPrototypeMethod(ctor, "atRaw", AtRaw);
	Nan::SetPrototypeMethod(ctor, "set", Set);
	Nan::SetPrototypeMethod(ctor, "push_back", PushBack);
	Nan::SetPrototypeMethod(ctor, "push_backAsync", PushBackAsync);
	Nan::SetPrototypeMethod(ctor, "pushBack", PushBack);
	Nan::SetPrototypeMethod(ctor, "pushBackAsync", PushBackAsync);
	Nan::SetPrototypeMethod(ctor, "pop_back", PopBack);
	Nan::SetPrototypeMethod(ctor, "pop_backAsync", PopBackAsync);
	Nan::SetPrototypeMethod(ctor, "popBack", PopBack);
	Nan::SetPrototypeMethod(ctor, "popBackAsync", PopBackAsync);
	Nan::SetPrototypeMethod(ctor, "getData", GetData);
	Nan::SetPrototypeMethod(ctor, "getDataAsync", GetDataAsync);
	Nan::SetPrototypeMethod(ctor, "getDataAsArray", GetDataAsArray);
	Nan::SetPrototypeMethod(ctor, "getRegion", GetRegion);
	Nan::SetPrototypeMethod(ctor, "row", Row);
	Nan::SetPrototypeMethod(ctor, "copy", Copy);
	Nan::SetPrototypeMethod(ctor, "copyAsync", CopyAsync);
	Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);
	Nan::SetPrototypeMethod(ctor, "copyToAsync", CopyToAsync);
	Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
	Nan::SetPrototypeMethod(ctor, "convertToAsync", ConvertToAsync);
	Nan::SetPrototypeMethod(ctor, "norm", Norm);
	Nan::SetPrototypeMethod(ctor, "normalize", Normalize);
	Nan::SetPrototypeMethod(ctor, "split", SplitChannels);
	Nan::SetPrototypeMethod(ctor, "splitAsync", SplitChannelsAsync);
	Nan::SetPrototypeMethod(ctor, "splitChannels", SplitChannels);
	Nan::SetPrototypeMethod(ctor, "splitChannelsAsync", SplitChannelsAsync);
	Nan::SetPrototypeMethod(ctor, "addWeighted", AddWeighted);
	Nan::SetPrototypeMethod(ctor, "addWeightedAsync", AddWeightedAsync);
	Nan::SetPrototypeMethod(ctor, "minMaxLoc", MinMaxLoc);
	Nan::SetPrototypeMethod(ctor, "minMaxLocAsync", MinMaxLocAsync);
	Nan::SetPrototypeMethod(ctor, "findNonZero", FindNonZero);
	Nan::SetPrototypeMethod(ctor, "findNonZeroAsync", FindNonZeroAsync);
	Nan::SetPrototypeMethod(ctor, "countNonZero", CountNonZero);
	Nan::SetPrototypeMethod(ctor, "countNonZeroAsync", CountNonZeroAsync);
	Nan::SetPrototypeMethod(ctor, "padToSquare", PadToSquare);
	Nan::SetPrototypeMethod(ctor, "padToSquareAsync", PadToSquareAsync);
	Nan::SetPrototypeMethod(ctor, "dct", Dct);
	Nan::SetPrototypeMethod(ctor, "dctAsync", DctAsync);
	Nan::SetPrototypeMethod(ctor, "idct", Idct);
	Nan::SetPrototypeMethod(ctor, "idctAsync", IdctAsync);
	Nan::SetPrototypeMethod(ctor, "dft", Dft);
	Nan::SetPrototypeMethod(ctor, "dftAsync", DftAsync);
	Nan::SetPrototypeMethod(ctor, "idft", Idft);
	Nan::SetPrototypeMethod(ctor, "idftAsync", IdftAsync);
	Nan::SetPrototypeMethod(ctor, "mulSpectrums", MulSpectrums);
	Nan::SetPrototypeMethod(ctor, "mulSpectrumsAsync", MulSpectrumsAsync);
	Nan::SetPrototypeMethod(ctor, "transform", Transform);
	Nan::SetPrototypeMethod(ctor, "transformAsync", TransformAsync);
	Nan::SetPrototypeMethod(ctor, "perspectiveTransform", PerspectiveTransform);
	Nan::SetPrototypeMethod(ctor, "perspectiveTransformAsync", PerspectiveTransformAsync);
	Nan::SetPrototypeMethod(ctor, "flip", Flip);
	Nan::SetPrototypeMethod(ctor, "flipAsync", FlipAsync);
	Nan::SetPrototypeMethod(ctor, "convertScaleAbs", ConvertScaleAbs);
	Nan::SetPrototypeMethod(ctor, "convertScaleAbsAsync", ConvertScaleAbsAsync);
	Nan::SetPrototypeMethod(ctor, "sum", Sum);
	Nan::SetPrototypeMethod(ctor, "sumAsync", SumAsync);
	Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrack", GoodFeaturesToTrack);
	Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrackAsync", GoodFeaturesToTrackAsync);
	Nan::SetPrototypeMethod(ctor, "meanStdDev", MeanStdDev);
	Nan::SetPrototypeMethod(ctor, "meanStdDevAsync", MeanStdDevAsync);
#if CV_VERSION_MINOR > 1
	Nan::SetPrototypeMethod(ctor, "rotate", Rotate);
	Nan::SetPrototypeMethod(ctor, "rotateAsync", RotateAsync);
#endif

	Nan::SetPrototypeMethod(ctor, "release", Release);

	FF_PROTO_SET_MAT_OPERATIONS(ctor);

	MatImgproc::Init(ctor);
	MatCalib3d::Init(ctor);

  target->Set(Nan::New("Mat").ToLocalChecked(), ctor->GetFunction());
};

// TODO type undefined throw error
NAN_METHOD(Mat::New) {
	Mat* self = new Mat();
	/* from channels */
	if (info.Length() == 1 && info[0]->IsArray()) {
		FF_ARR jsChannelMats = FF_ARR::Cast(info[0]);
		std::vector<cv::Mat> channels;
		for (int i = 0; i < jsChannelMats->Length(); i++) {
			FF_OBJ jsChannelMat = FF_CAST_OBJ(jsChannelMats->Get(i));
			FF_REQUIRE_INSTANCE(constructor, jsChannelMat,
				FF_NEW_STRING("expected channel " + std::to_string(i) + " to be an instance of Mat"));
			cv::Mat channelMat = FF_UNWRAP_MAT_AND_GET(jsChannelMat);
			channels.push_back(channelMat);
			if (i > 0) {
				FF_ASSERT_EQUALS(channels.at(i - 1).rows, channelMat.rows, "Mat::New - rows", " at channel " + std::to_string(i));
				FF_ASSERT_EQUALS(channels.at(i - 1).cols, channelMat.cols, "Mat::New - cols", " at channel " + std::to_string(i));
			}
		}
		cv::Mat mat;
		cv::merge(channels, mat);
		self->setNativeProps(mat);
	}
	/* data array, type */
	else if (info.Length() == 2 && info[0]->IsArray() && info[1]->IsInt32()) {
		FF_ARR rowArray = FF_ARR::Cast(info[0]);
		int type = info[1]->Int32Value();

		int numCols = -1;
		for (uint i = 0; i < rowArray->Length(); i++) {
			if (!rowArray->Get(i)->IsArray()) {
				return Nan::ThrowError(Nan::New("Mat::New - Column should be an array, at column: " + std::to_string(i)).ToLocalChecked());
			}
			FF_ARR colArray = FF_ARR::Cast(rowArray->Get(i));
			if (numCols != -1 && numCols != colArray->Length()) {
				return Nan::ThrowError(Nan::New("Mat::New - Mat cols must be of uniform length, at column: " + std::to_string(i)).ToLocalChecked());
			}
			numCols = colArray->Length();
		}

		cv::Mat mat = cv::Mat(rowArray->Length(), numCols, type);
		FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, type, FF_MAT_FROM_JS_ARRAY, FF::matPut);
		self->setNativeProps(mat);
	}
	/* row, col, type */
	else if (info[0]->IsNumber() && info[1]->IsNumber() && info[2]->IsInt32()) {
		int type = info[2]->Int32Value();
		cv::Mat mat(info[0]->Int32Value(), info[1]->Int32Value(), type);
		/* fill vector */
		// TODO by Vec
		if (info[3]->IsArray()) {
			FF_ARR vec = FF_ARR::Cast(info[3]);
			if (mat.channels() != vec->Length()) {
				return Nan::ThrowError(FF_NEW_STRING(
					std::string("Mat::New - number of channels (") + std::to_string(mat.channels())
					+ std::string(") do not match fill vector length ") + std::to_string(vec->Length()))
				);
			}
			FF_MAT_APPLY_TYPED_OPERATOR(mat, vec, type, FF_MAT_FILL, FF::matPut);
		}
		if (info[3]->IsNumber()) {
			FF_MAT_APPLY_TYPED_OPERATOR(mat, info[3], type, FF_MAT_FILL, FF::matPut);
		}
		self->setNativeProps(mat);
	}
	/* raw data, row, col, type */
	else if (info.Length() == 4 && info[1]->IsNumber() && info[2]->IsNumber() && info[3]->IsInt32()) {
		int type = info[3]->Int32Value();
		char *data = static_cast<char *>(node::Buffer::Data(info[0]->ToObject()));
		cv::Mat mat(info[1]->Int32Value(), info[2]->Int32Value(), type);
		size_t size = mat.rows * mat.cols * mat.elemSize();
		memcpy(mat.data, data, size);
		self->setNativeProps(mat);
	}
	self->Wrap(info.Holder());
    
	// if ExternalMemTracking is disabled, the following instruction will be a no op
    // notes: I *think* New should be called in JS thread where cv::mat has been created async,
    // so a good place to rationalise memory
	ExternalMemTracking::onMatAllocated();

	FF_RETURN(info.Holder());
}

NAN_METHOD(Mat::Eye) {
	FF_METHOD_CONTEXT("Mat::Eye");
	FF_ARG_INT(0, int rows);
	FF_ARG_INT(1, int cols);
	FF_ARG_INT(2, int type);
	FF_OBJ jsEyeMat = FF_NEW_INSTANCE(Mat::constructor);
	FF_UNWRAP_MAT_AND_GET(jsEyeMat) = cv::Mat::eye(cv::Size(cols, rows), type);
	FF_RETURN(jsEyeMat);
}

// squash multidimensional Mat into 2D Mat
// TODO: figure out how to deal with multidim Mats
NAN_METHOD(Mat::FlattenFloat) {
	FF_METHOD_CONTEXT("Mat::To2DFloat");
	FF_ARG_INT(0, int rows);
	FF_ARG_INT(1, int cols);

	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	cv::Mat mat2D(rows, cols, CV_32F, matSelf.ptr<float>());
	FF_RETURN(Mat::Converter::wrap(mat2D));
}

NAN_METHOD(Mat::At) {
	FF_METHOD_CONTEXT("Mat::At");
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::At row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::At col");
	v8::Local<v8::Value> val;
	FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
	v8::Local<v8::Value> jsVal;
	if (val->IsArray()) {
		FF_ARR vec = FF_ARR::Cast(val);
		FF_OBJ jsVec;
		if (vec->Length() == 2) {
			jsVec = FF_NEW_INSTANCE(Vec2::constructor);
			FF_UNWRAP_VEC2(jsVec)->vec = cv::Vec2d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue());
		}
		else if (vec->Length() == 3) {
			jsVec = FF_NEW_INSTANCE(Vec3::constructor);
			FF_UNWRAP_VEC3(jsVec)->vec = cv::Vec3d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue());
		}
		else {
			jsVec = FF_NEW_INSTANCE(Vec4::constructor);
			FF_UNWRAP_VEC4(jsVec)->vec = cv::Vec4d(vec->Get(0)->NumberValue(), vec->Get(1)->NumberValue(), vec->Get(2)->NumberValue(), vec->Get(3)->NumberValue());
		}
		jsVal = jsVec;
	}
	else {
		jsVal = v8::Local<v8::Value>::Cast(val);
	}
	FF_RETURN(jsVal);
}

NAN_METHOD(Mat::AtRaw) {
	FF_METHOD_CONTEXT("Mat::AtRaw");
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::At row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::At col");
	v8::Local<v8::Value> val;
	FF_MAT_APPLY_TYPED_OPERATOR(matSelf, val, matSelf.type(), FF_MAT_AT, FF::matGet);
	FF_RETURN(val);
}

NAN_METHOD(Mat::Set) {
	FF_METHOD_CONTEXT("Mat::Set");
	cv::Mat matSelf = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), matSelf.rows - 1, "Mat::Set row");
	FF_ASSERT_INDEX_RANGE(info[1]->Int32Value(), matSelf.cols - 1, "Mat::Set col");

	int cn = matSelf.channels();
	if (info[2]->IsArray()) {
		FF_ARR vec = FF_ARR::Cast(info[2]);
		FF_ASSERT_CHANNELS(cn, vec->Length(), "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, vec, matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (FF_IS_INSTANCE(Vec2::constructor, info[2])) {
		FF_ASSERT_CHANNELS(cn, 2, "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<2>(FF_UNWRAP_VEC2_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (FF_IS_INSTANCE(Vec3::constructor, info[2])) {
		FF_ASSERT_CHANNELS(cn, 3, "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<3>(FF_UNWRAP_VEC3_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (FF_IS_INSTANCE(Vec4::constructor, info[2])) {
		FF_ASSERT_CHANNELS(cn, 4, "Mat::Set");
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, FF::vecToJsArr<4>(FF_UNWRAP_VEC4_AND_GET(info[2]->ToObject())), matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else if (info[2]->IsNumber()) {
		FF_MAT_APPLY_TYPED_OPERATOR(matSelf, info[2], matSelf.type(), FF_MAT_SET, FF::matPut);
	}
	else {
		return Nan::ThrowError(FF_NEW_STRING("Mat::Set - unexpected argument 2"));
	}
}

struct Mat::PushBackWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	PushBackWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat mat;

	std::string executeCatchCvExceptionWorker() {
		self.push_back(mat);
		return "";
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &mat, info)
		);
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(self);
	}
};

NAN_METHOD(Mat::PushBack) {
	PushBackWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::PushBack", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::PushBackAsync) {
	PushBackWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::PushBackAsync", PushBackWorker, worker);
}


struct Mat::PopBackWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	PopBackWorker(cv::Mat self) {
		this->self = self;
	}

	int num = 1;

	std::string executeCatchCvExceptionWorker() {
		self.pop_back(num);
		return "";
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(0, &num, info)
		);
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(self);
	}
};

NAN_METHOD(Mat::PopBack) {
	PopBackWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::PopBack", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::PopBackAsync) {
	PopBackWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::PopBackAsync", PopBackWorker, worker);
}

struct Mat::GetDataWorker : CatchCvExceptionWorker {
public:
	cv::Mat mat;

	GetDataWorker(cv::Mat mat) {
		this->mat = mat;
	}

	size_t size;
	char *data;

	std::string executeCatchCvExceptionWorker() {
		size = mat.rows * mat.cols * mat.elemSize();
		data = static_cast<char *>(malloc(size));
		memcpy(data, mat.data, size);
		return "";
	}

	static void freeBufferCallback(char* data, void* hint) {
		free(data);
	}

	FF_VAL getReturnValue() {
		return Nan::NewBuffer(data, size, freeBufferCallback, 0).ToLocalChecked();
	}
};

NAN_METHOD(Mat::GetData) {
	GetDataWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::GetData", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::GetDataAsync) {
	GetDataWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::GetDataAsync", GetDataWorker, worker);
}

NAN_METHOD(Mat::GetDataAsArray) {
	cv::Mat mat = FF_UNWRAP_MAT_AND_GET(info.This());
	FF_ARR rowArray = FF_NEW_ARRAY(mat.rows);
	FF_MAT_APPLY_TYPED_OPERATOR(mat, rowArray, mat.type(), FF_JS_ARRAY_FROM_MAT, FF::matGet);
	FF_RETURN(rowArray);
}

NAN_METHOD(Mat::GetRegion) {
	if (!FF_IS_INSTANCE(Rect::constructor, info[0])) {
		Nan::ThrowError("Mat::GetRegion expected arg0 to be an instance of Rect");
	}
	cv::Rect2d rect = FF_UNWRAP(info[0]->ToObject(), Rect)->rect;
	FF_OBJ jsRegion = FF_NEW_INSTANCE(constructor);
	FF_UNWRAP_MAT_AND_GET(jsRegion) = FF_UNWRAP_MAT_AND_GET(info.This())(rect);
	FF_RETURN(jsRegion);
}

struct Mat::CopyWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	CopyWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat dst;
	cv::Mat mask = cv::noArray().getMat();

	std::string executeCatchCvExceptionWorker() {
		self.copyTo(dst, mask);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::optArg(0, &mask, info)
		);
	}
};

NAN_METHOD(Mat::Copy) {
	CopyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Copy", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::CopyAsync) {
	CopyWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CopyAsync", CopyWorker, worker);
}


struct Mat::CopyToWorker : public CopyWorker {
public:
	CopyToWorker(cv::Mat self) : CopyWorker(self){
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &dst, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::optArg(1, &mask, info)
		);
	}
};

NAN_METHOD(Mat::CopyTo) {
	CopyToWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CopyTo", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::CopyToAsync) {
	CopyToWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CopyToAsync", CopyToWorker, worker);
}


struct Mat::ConvertToWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	ConvertToWorker(cv::Mat self) {
		this->self = self;
	}

	int rtype;
	double alpha = 1.0;
	double beta = 0.0;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		self.convertTo(dst, rtype, alpha, beta);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &rtype, info)
		);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(1, &alpha, info) ||
			DoubleConverter::optArg(2, &beta, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[1]->ToObject();
		return (
			DoubleConverter::optProp(&alpha, "alpha", opts) ||
			DoubleConverter::optProp(&beta, "beta", opts)
		);
	}
};

NAN_METHOD(Mat::ConvertTo) {
	ConvertToWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::ConvertTo", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::ConvertToAsync) {
	ConvertToWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ConvertToAsync", ConvertToWorker, worker);
}

NAN_METHOD(Mat::Norm) {
	FF_METHOD_CONTEXT("Mat::Norm");

	bool withSrc2 = FF_HAS_ARG(0) && FF_IS_INSTANCE(Mat::constructor, info[0]);
	uint i = withSrc2 ? 1 : 0;
	double norm;

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(i) && info[i]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[i]->ToObject() : FF_NEW_OBJ();
	FF_GET_UINT_IFDEF(optArgs, uint normType, "normType", cv::NORM_L2);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Mat mask, "mask", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
	if (!hasOptArgsObj) {
		FF_ARG_UINT_IFDEF(i, normType, normType);
		FF_ARG_INSTANCE_IFDEF(i + 1, mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, mask);
	}

	if (withSrc2) {
		FF_ARG_INSTANCE(0, cv::Mat src2, Mat::constructor, FF_UNWRAP_MAT_AND_GET);
		norm = cv::norm(FF_UNWRAP_MAT_AND_GET(info.This()), src2, (int)normType, mask);
	}
	else {
		norm = cv::norm(FF_UNWRAP_MAT_AND_GET(info.This()), (int)normType, mask);
	}
	FF_RETURN(norm);
}

NAN_METHOD(Mat::Normalize) {
	FF_METHOD_CONTEXT("Mat::Normalize");

	// optional args
	bool hasOptArgsObj = FF_HAS_ARG(0) && info[0]->IsObject();
	FF_OBJ optArgs = hasOptArgsObj ? info[0]->ToObject() : FF_NEW_OBJ();
	FF_GET_NUMBER_IFDEF(optArgs, double alpha, "alpha", 1.0);
	FF_GET_NUMBER_IFDEF(optArgs, double beta, "beta", 0.0);
	FF_GET_UINT_IFDEF(optArgs, uint normType, "normType", cv::NORM_L2);
	FF_GET_UINT_IFDEF(optArgs, int dtype, "dtype", -1);
	FF_GET_INSTANCE_IFDEF(optArgs, cv::Mat mask, "mask", Mat::constructor, FF_UNWRAP_MAT_AND_GET, Mat, cv::noArray().getMat());
	if (!hasOptArgsObj) {
		FF_ARG_NUMBER_IFDEF(0, alpha, 1.0);
		FF_ARG_NUMBER_IFDEF(1, beta, 0.0);
		FF_ARG_UINT_IFDEF(3, normType, normType);
		FF_ARG_INT_IFDEF(4, dtype, dtype);
		FF_ARG_INSTANCE_IFDEF(5, mask, Mat::constructor, FF_UNWRAP_MAT_AND_GET, mask);
	}

	FF_OBJ jsMat = FF_NEW_INSTANCE(constructor);
	cv::normalize(FF_UNWRAP_MAT_AND_GET(info.This()), FF_UNWRAP_MAT_AND_GET(jsMat), alpha, beta, normType, dtype, mask);
	FF_RETURN(jsMat);
}

struct Mat::SplitChannelsWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	SplitChannelsWorker(cv::Mat self) {
		this->self = self;
	}


	std::vector<cv::Mat> mv;

	std::string executeCatchCvExceptionWorker() {
		cv::split(self, mv);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return ObjectArrayConverter<Mat, cv::Mat> ::wrap(mv);
	}
};

NAN_METHOD(Mat::SplitChannels) {
	SplitChannelsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::SplitChannels", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::SplitChannelsAsync) {
	SplitChannelsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::SplitChannelsAsync", SplitChannelsWorker, worker);
}

struct Mat::AddWeightedWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	AddWeightedWorker(cv::Mat self) {
		this->self = self;
	}

	double alpha;
	cv::Mat src2;
	double beta;
	double gamma;
	int dtype = -1;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::addWeighted(self, alpha, src2, beta, gamma, dst, dtype);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::arg(0, &alpha, info) ||
			Mat::Converter::arg(1, &src2, info) ||
			DoubleConverter::arg(2, &beta, info) ||
			DoubleConverter::arg(3, &gamma, info)
			);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(4, &dtype, info)
		);
	}
};

NAN_METHOD(Mat::AddWeighted) {
	AddWeightedWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::AddWeighted", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::AddWeightedAsync) {
	AddWeightedWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::AddWeightedAsync", AddWeightedWorker, worker);
}


struct Mat::MinMaxLocWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	MinMaxLocWorker(cv::Mat self) {
		this->self = self;
	}

	double minVal, maxVal;
	cv::Point2i minLoc, maxLoc;
	cv::Mat mask = cv::noArray().getMat();

	std::string executeCatchCvExceptionWorker() {
		cv::minMaxLoc(self, &minVal, &maxVal, &minLoc, &maxLoc, mask);
		return "";
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::optArg(0, &mask, info);
	}

	v8::Local<v8::Value> getReturnValue() {
		FF_OBJ ret = FF_NEW_OBJ();
		Nan::Set(ret, FF_NEW_STRING("minVal"), Nan::New(minVal));
		Nan::Set(ret, FF_NEW_STRING("maxVal"), Nan::New(maxVal));
		Nan::Set(ret, FF_NEW_STRING("minLoc"), Point2::Converter::wrap(minLoc));
		Nan::Set(ret, FF_NEW_STRING("maxLoc"), Point2::Converter::wrap(maxLoc));
		return ret;
	}
};

NAN_METHOD(Mat::MinMaxLoc) {
	MinMaxLocWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MinMaxLoc", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::MinMaxLocAsync) {
	MinMaxLocWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MinMaxLocAsync", MinMaxLocWorker, worker);
}

struct Mat::FindNonZeroWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	FindNonZeroWorker(cv::Mat self) {
		this->self = self;
	}

	std::vector<cv::Point> idx;

	std::string executeCatchCvExceptionWorker() {
		cv::findNonZero(self, idx);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return ObjectArrayConverter<Point2, cv::Point2d, cv::Point>::wrap(idx);
	}
};

NAN_METHOD(Mat::FindNonZero) {
	FindNonZeroWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::FindNonZero", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::FindNonZeroAsync) {
	FindNonZeroWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::FindNonZeroAsync", FindNonZeroWorker, worker);
}

struct Mat::CountNonZeroWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	CountNonZeroWorker(cv::Mat self) {
		this->self = self;
	}

	int num;

	std::string executeCatchCvExceptionWorker() {
		num = cv::countNonZero(self);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return IntConverter::wrap(num);
	}
};

NAN_METHOD(Mat::CountNonZero) {
	CountNonZeroWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::CountNonZero", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::CountNonZeroAsync) {
	CountNonZeroWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::CountNonZeroAsync", CountNonZeroWorker, worker);
}

struct Mat::PadToSquareWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	PadToSquareWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Vec3d fillVec = cv::Vec3d();
	cv::Mat out;
	std::string executeCatchCvExceptionWorker() {
		int maxDim = (std::max)(self.cols, self.rows);
		out = cv::Mat(maxDim, maxDim, self.type(), (cv::Vec3b)fillVec);

		int offX = 0, offY = 0;
		if (self.cols > self.rows) {
			offY = (self.cols - self.rows) / 2;
		}
		else {
			offX = (self.rows - self.cols) / 2;
		}
		cv::Mat roi = out(cv::Rect(offX, offY, self.cols, self.rows));
		self.copyTo(roi);

		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(out);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Vec3::Converter::optArg(0, &fillVec, info);
	}
};

NAN_METHOD(Mat::PadToSquare) {
	PadToSquareWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::PadToSquare", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::PadToSquareAsync) {
	PadToSquareWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::PadToSquareAsync", PadToSquareWorker, worker);
}

struct Mat::DTWorker : public CatchCvExceptionWorker {
public:
	cv::Mat mat;
	bool isInverse;

	DTWorker(cv::Mat mat, bool isInverse) {
		this->mat = mat;
		this->isInverse = isInverse;
	}

	int flags = 0;

	cv::Mat dst;

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return false;
	}
};

struct Mat::DCTWorker : public DTWorker {
	DCTWorker(cv::Mat mat, bool isInverse = false) : DTWorker(mat, isInverse) {
	}

	std::string executeCatchCvExceptionWorker() {
		if (isInverse) {
			cv::idct(mat, dst, flags);
		}
		else {
			cv::dct(mat, dst, flags);
		}
		return "";
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return IntConverter::optArg(0, &flags, info);
	}
};

struct Mat::DFTWorker : public DTWorker {
	DFTWorker(cv::Mat mat, bool isInverse = false) : DTWorker(mat, isInverse) {
	}

	int nonzeroRows = 0;

	std::string executeCatchCvExceptionWorker() {
		if (isInverse) {
			cv::idft(mat, dst, flags, nonzeroRows);
		}
		else {
			cv::dft(mat, dst, flags, nonzeroRows);
		}
		return "";
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::optArg(0, &flags, info) ||
			IntConverter::optArg(1, &nonzeroRows, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[0]->ToObject();
		return (
			IntConverter::optProp(&flags, "flags", opts) ||
			IntConverter::optProp(&nonzeroRows, "nonzeroRows", opts)
		);
	}
};

NAN_METHOD(Mat::Dct) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Dct", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::DctAsync) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DctAsync", DCTWorker, worker);
}

NAN_METHOD(Mat::Idct) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::Idct", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::IdctAsync) {
	DCTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::IdctAsync", DCTWorker, worker);
}

NAN_METHOD(Mat::Dft) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Dft", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::DftAsync) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::DftAsync", DFTWorker, worker);
}

NAN_METHOD(Mat::Idft) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_SYNC("Mat::Idft", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::IdftAsync) {
	DFTWorker worker(Mat::Converter::unwrap(info.This()), true);
	FF_WORKER_ASYNC("Mat::IdftAsync", DFTWorker, worker);
}

struct Mat::MulSpectrumsWorker : public CatchCvExceptionWorker {
public:
	cv::Mat mat;
	bool isInverse;

	MulSpectrumsWorker(cv::Mat mat) {
		this->mat = mat;
	}

	cv::Mat mat2;
	bool dftRows = false;
	bool conjB = false;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		int flags = (dftRows ? cv::DFT_ROWS : 0);
		cv::mulSpectrums(mat, mat2, dst, flags, conjB);
		return "";
	}

	FF_VAL getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return Mat::Converter::arg(0, &mat2, info);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			BoolConverter::optArg(1, &dftRows, info) ||
			BoolConverter::optArg(2, &conjB, info)
		);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(1);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		FF_OBJ opts = info[1]->ToObject();
		return (
			BoolConverter::optProp(&dftRows, "dftRows", opts) ||
			BoolConverter::optProp(&conjB, "conjB", opts)
		);
	}
};

NAN_METHOD(Mat::MulSpectrums) {
	MulSpectrumsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MulSpectrums", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::MulSpectrumsAsync) {
	MulSpectrumsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MulSpectrumsAsync", MulSpectrumsWorker, worker);
}


struct Mat::TransformWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	TransformWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat m;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::transform(self, dst, m);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::arg(0, &m, info)
		);
	}
};

NAN_METHOD(Mat::Transform) {
	TransformWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Transform", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::TransformAsync) {
	TransformWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::TransformAsync", TransformWorker, worker);
}

struct Mat::PerspectiveTransformWorker : public Mat::TransformWorker {
public:
	PerspectiveTransformWorker(cv::Mat self) : Mat::TransformWorker(self) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::perspectiveTransform(self, dst, m);
		return "";
	}
};

NAN_METHOD(Mat::PerspectiveTransform) {
	PerspectiveTransformWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::PerspectiveTransform", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::PerspectiveTransformAsync) {
	PerspectiveTransformWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::PerspectiveTransformAsync", PerspectiveTransformWorker, worker);
}


struct Mat::OpWithCodeWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	OpWithCodeWorker(cv::Mat self) {
		this->self = self;
	}

	int code;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::flip(self, dst, code);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &code, info)
		);
	}
};

struct Mat::FlipWorker : public OpWithCodeWorker {
public:
	FlipWorker(cv::Mat self) : OpWithCodeWorker(self) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::flip(self, dst, code);
		return "";
	}
};

NAN_METHOD(Mat::Flip) {
	FlipWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Flip", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::FlipAsync) {
	FlipWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::FlipAsync", FlipWorker, worker);
}

struct Mat::SumWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	SumWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Scalar sum;

	std::string executeCatchCvExceptionWorker() {
		sum = cv::sum(self);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		switch (self.channels()) {
		case 1:
			return DoubleConverter::wrap(sum[0]);
		case 2:
			return Vec2::Converter::wrap(cv::Vec2f(sum[0], sum[1]));
		case 3:
			return Vec3::Converter::wrap(cv::Vec3f(sum[0], sum[1], sum[2]));
		case 4:
			return Vec4::Converter::wrap(cv::Vec4f(sum));
		default:
			return Nan::Undefined();
		}
	}
};

NAN_METHOD(Mat::Sum) {
	SumWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Sum", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::SumAsync) {
	SumWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::SumAsync", SumWorker, worker);
}


struct Mat::ConvertScaleAbsWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	ConvertScaleAbsWorker(cv::Mat self) {
		this->self = self;
	}

	double alpha = 1;
	double beta = 0;

	cv::Mat dst;

	std::string executeCatchCvExceptionWorker() {
		cv::convertScaleAbs(self, dst, alpha, beta);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		return Mat::Converter::wrap(dst);
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			DoubleConverter::optArg(0, &alpha, info) ||
			DoubleConverter::optArg(1, &beta, info)
			);
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(0);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[0]->ToObject();
		return (
			DoubleConverter::optProp(&alpha, "alpha", opts) ||
			DoubleConverter::optProp(&beta, "beta", opts)
			);
	}
};

NAN_METHOD(Mat::ConvertScaleAbs) {
	ConvertScaleAbsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::ConvertScaleAbs", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::ConvertScaleAbsAsync) {
	ConvertScaleAbsWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::ConvertScaleAbsAsync", ConvertScaleAbsWorker, worker);
}


struct Mat::GoodFeaturesToTrackWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	GoodFeaturesToTrackWorker(cv::Mat self) {
		this->self = self;
	}

	// required function arguments
	int maxCorners;
	double qualityLevel;
	double minDistance;

	// optional args
	cv::Mat mask = cv::noArray().getMat();
	// default values from: https://docs.opencv.org/3.4.1/dd/d1a/group__imgproc__feature.html#ga1d6bb77486c8f92d79c8793ad995d541
	int blockSize = 3;
	int gradientSize = 3;
	bool useHarrisDetector = false;
	double harrisK = 0.04;

	// function return value
	std::vector<cv::Point2f> corners;

	bool unwrapRequiredArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			IntConverter::arg(0, &maxCorners, info) ||
			DoubleConverter::arg(1, &qualityLevel, info) ||
			DoubleConverter::arg(2, &minDistance, info)
		);
	}
	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		// if 5th arg is Boolean, then we check for the 7 param signature
		if (info[5]->IsBoolean()){
			return (
				Mat::Converter::optArg(3, &mask, info) ||
				IntConverter::optArg(4, &blockSize, info) ||
				BoolConverter::optArg(5, &useHarrisDetector, info) ||
				DoubleConverter::optArg(6, &harrisK, info)
			);

		} // else we check for the 8 param signature
		else {
			return (
				Mat::Converter::optArg(3, &mask, info) ||
				IntConverter::optArg(4, &blockSize, info) ||
				IntConverter::optArg(5, &gradientSize, info) ||
				BoolConverter::optArg(6, &useHarrisDetector, info) ||
				DoubleConverter::optArg(7, &harrisK, info)
			);
		}
	}

	bool hasOptArgsObject(Nan::NAN_METHOD_ARGS_TYPE info) {
		return FF_ARG_IS_OBJECT(3);
	}

	bool unwrapOptionalArgsFromOpts(Nan::NAN_METHOD_ARGS_TYPE info) {
		v8::Local<v8::Object> opts = info[3]->ToObject();
		return (
			Mat::Converter::optProp(&mask, "mask", opts) ||
			IntConverter::optProp(&blockSize, "blockSize", opts) ||
			IntConverter::optProp(&gradientSize, "gradientSize", opts) ||
			BoolConverter::optProp(&useHarrisDetector, "useHarrisDetector", opts) ||
			DoubleConverter::optProp(&harrisK, "harrisK", opts)
		);
	}


	std::string executeCatchCvExceptionWorker() {
#if CV_VERSION_MINOR >= 4
		cv::goodFeaturesToTrack(
				self, corners,
				maxCorners, qualityLevel, minDistance,
				mask, blockSize, gradientSize,
				useHarrisDetector, harrisK);
#else
		cv::goodFeaturesToTrack(
				self, corners,
				maxCorners, qualityLevel, minDistance,
				mask, blockSize,
				useHarrisDetector, harrisK);
#endif
		return "";
	}

	FF_VAL getReturnValue() {
		return ObjectArrayConverter<Point2, cv::Point2f>::wrap(corners);
	}
};

NAN_METHOD(Mat::GoodFeaturesToTrack) {
	GoodFeaturesToTrackWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::GoodFeaturesToTrack", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::GoodFeaturesToTrackAsync) {
	GoodFeaturesToTrackWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::GoodFeaturesToTrackAsync", GoodFeaturesToTrackWorker, worker);
}

struct Mat::MeanStdDevWorker : public CatchCvExceptionWorker {
public:
	cv::Mat self;
	MeanStdDevWorker(cv::Mat self) {
		this->self = self;
	}

	cv::Mat mask = cv::noArray().getMat();

	cv::Mat mean;
	cv::Mat stddev;

	std::string executeCatchCvExceptionWorker() {
		cv::meanStdDev(self, mean, stddev, mask);
		return "";
	}

	v8::Local<v8::Value> getReturnValue() {
		v8::Local<v8::Object> ret = Nan::New<v8::Object>();
		Nan::Set(ret, Nan::New("mean").ToLocalChecked(), Mat::Converter::wrap(mean));
		Nan::Set(ret, Nan::New("stddev").ToLocalChecked(), Mat::Converter::wrap(stddev));
		return ret;
	}

	bool unwrapOptionalArgs(Nan::NAN_METHOD_ARGS_TYPE info) {
		return (
			Mat::Converter::optArg(0, &mask, info)
		);
	}
};

NAN_METHOD(Mat::MeanStdDev) {
	MeanStdDevWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::MeanStdDev", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::MeanStdDevAsync) {
	MeanStdDevWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::MeanStdDevAsync", MeanStdDevWorker, worker);
}

#if CV_VERSION_MINOR > 1
struct Mat::RotateWorker : public OpWithCodeWorker {
public:
	RotateWorker(cv::Mat self) : OpWithCodeWorker(self) {
	}

	std::string executeCatchCvExceptionWorker() {
		cv::rotate(self, dst, code);
		return "";
	}
};

NAN_METHOD(Mat::Rotate) {
	RotateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_SYNC("Mat::Rotate", worker);
	info.GetReturnValue().Set(worker.getReturnValue());
}

NAN_METHOD(Mat::RotateAsync) {
	RotateWorker worker(Mat::Converter::unwrap(info.This()));
	FF_WORKER_ASYNC("Mat::RotateAsync", RotateWorker, worker);
}
#endif


NAN_METHOD(Mat::Row) {
  if (!info[0]->IsNumber()) {
    return Nan::ThrowError("usage: row(int r)");
  }
  int r = (int)info[0]->NumberValue();
  cv::Mat mat = Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat;
  FF_ARR row = FF_NEW_ARRAY(mat.cols);
  try {
    if (mat.type() == CV_32FC1) {
      for (int c = 0;  c < mat.cols; c++) {
        row->Set(c, Nan::New(mat.at<float>(r, c)));
      }
    } else if (mat.type() == CV_8UC1) {
      for (int c = 0;  c < mat.cols; c++) {
        row->Set(c, Nan::New((uint)mat.at<uchar>(r, c)));
      }
    } else if (mat.type() == CV_8UC3) {
      for (int c = 0;  c < mat.cols; c++) {
        cv::Vec3b vec = mat.at<cv::Vec3b>(r, c);
        FF_ARR jsVec = FF_NEW_ARRAY(3);
        for (int i = 0; i < 3; i++) {
          jsVec->Set(i, Nan::New(vec[i]));
        }
        row->Set(c, jsVec);
      }
    } else {
      return Nan::ThrowError(Nan::New("not implemented yet - mat type:" + mat.type()).ToLocalChecked());
    }
  } catch(std::exception &e) {
    return Nan::ThrowError(e.what());
  } catch(...) {
    return Nan::ThrowError("... Exception");
  }
  FF_RETURN(row);
}

void Mat::setNativeProps(cv::Mat mat) {
	this->mat = mat;
};

// free memory for this mat
NAN_METHOD(Mat::Release) {
    // must get pointer to the original; else we are just getting a COPY and then releasing that!
    cv::Mat *mat = &(Nan::ObjectWrap::Unwrap<Mat>(info.This())->mat);
    mat->release();
}


