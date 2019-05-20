#include "Contour.h"
#include "ContourBindings.h"
#include "Mat.h"
#include "Point.h"
#include "Rect.h"
#include "RotatedRect.h"
#include "Moments.h"

Nan::Persistent<v8::FunctionTemplate> Contour::constructor;

NAN_MODULE_INIT(Contour::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Contour::New);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("Contour").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("isConvex"), GetIsConvex);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("area"), GetArea);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("numPoints"), GetNumPoints);
	Nan::SetAccessor(ctor->InstanceTemplate(), FF_NEW_STRING("hierarchy"), GetHierarchy);

	Nan::SetPrototypeMethod(ctor, "getPoints", GetPoints);
	Nan::SetPrototypeMethod(ctor, "approxPolyDP", ApproxPolyDP);
	Nan::SetPrototypeMethod(ctor, "approxPolyDPAsync", ApproxPolyDPAsync);
	Nan::SetPrototypeMethod(ctor, "approxPolyDPContour", ApproxPolyDPContour);
	Nan::SetPrototypeMethod(ctor, "arcLength", ArcLength);
	Nan::SetPrototypeMethod(ctor, "boundingRect", BoundingRect);
	Nan::SetPrototypeMethod(ctor, "convexHull", ConvexHull);
	Nan::SetPrototypeMethod(ctor, "convexHullIndices", ConvexHullIndices);
	Nan::SetPrototypeMethod(ctor, "convexityDefects", ConvexityDefects);
	Nan::SetPrototypeMethod(ctor, "minAreaRect", MinAreaRect);
	Nan::SetPrototypeMethod(ctor, "minEnclosingCircle", MinEnclosingCircle);
	Nan::SetPrototypeMethod(ctor, "minEnclosingTriangle", MinEnclosingTriangle);
	Nan::SetPrototypeMethod(ctor, "pointPolygonTest", PointPolygonTest);
	Nan::SetPrototypeMethod(ctor, "matchShapes", MatchShapes);
	Nan::SetPrototypeMethod(ctor, "fitEllipse", FitEllipse);
	Nan::SetPrototypeMethod(ctor, "moments", _Moments);

	target->Set(Nan::New("Contour").ToLocalChecked(), FF::getFunction(ctor));
};

NAN_METHOD(Contour::New) {
	FF_ASSERT_CONSTRUCT_CALL(Contour);
	if (info.Length() > 1) {
		return Nan::ThrowError("Contour::New - expected one or zero argument");
	}
	if (info.Length() == 1 && !info[0]->IsArray()) {
		return Nan::ThrowError("Contour::New - expected arg0 to be an array");
	}

	Contour* self = new Contour();
	if (info.Length() == 1) {
		FF_ARR jsPts = FF_ARR::Cast(info[0]);
		self->contour.reserve(jsPts->Length());
		for (uint i = 0; i < jsPts->Length(); i++) {
			cv::Point2d cv_pt;
			auto jsPt = jsPts->Get(i);
			if (jsPt->IsArray()) {
				FF_ARR jsObj = FF_ARR::Cast(jsPt);
				if (jsObj->Length() != 2)
					return Nan::ThrowError("Contour::New - expected arg0 to consist of only Point2 or array of length 2");
				double x = jsObj->Get(0)->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
				double y = jsObj->Get(1)->ToNumber(Nan::GetCurrentContext()).ToLocalChecked()->Value();
				cv_pt = cv::Point2d(x, y);
			}
			else if (FF_IS_INSTANCE(Point2::constructor, jsPt)) {
				FF_OBJ jsObj = FF_CAST_OBJ(jsPt);
				cv_pt = FF_UNWRAP_PT2_AND_GET(jsObj);
			}
			else {
				return Nan::ThrowError("Contour::New - expected arg0 to consist of only Point2 or array of length 2");
			}
			self->contour.emplace_back(cv::Point2i(cv_pt.x, cv_pt.y));
		}
	}
	self->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	self->Wrap(info.Holder());
	info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Contour::GetPoints) {
	info.GetReturnValue().Set(ObjectArrayConverter<Point2, cv::Point2d, cv::Point2i>::wrap(FF_UNWRAP_CONTOUR_AND_GET(info.This())));
}

NAN_METHOD(Contour::ApproxPolyDP) {
	FF::SyncBinding(
		std::make_shared<ContourBindings::ApproxPolyDPWorker>(Contour::Converter::unwrap(info.This())),
		"Contour::ApproxPolyDP",
		info
	);
}

NAN_METHOD(Contour::ApproxPolyDPAsync) {
	FF::AsyncBinding(
		std::make_shared<ContourBindings::ApproxPolyDPWorker>(Contour::Converter::unwrap(info.This())),
		"Contour::ApproxPolyDPAsync",
		info
	);
}

NAN_METHOD(Contour::ApproxPolyDPContour) {
	FF::TryCatch tryCatch;
	double epsilon;
	bool closed;
	if (
		DoubleConverter::arg(0, &epsilon, info) ||
		BoolConverter::arg(1, &closed, info)
	) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Contour::ApproxPolyDPContour"));
		return;
	}

	std::vector<cv::Point> curve;
	cv::approxPolyDP(FF_UNWRAP_CONTOUR_AND_GET(info.This()), curve, epsilon, closed);

	FF_OBJ jsApprox = FF::newInstance(Nan::New(Contour::constructor));
	FF_UNWRAP_CONTOUR_AND_GET(jsApprox) = curve;
	FF_UNWRAP(jsApprox, Contour)->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	FF_RETURN(jsApprox);
}

NAN_METHOD(Contour::ArcLength) {
	FF::TryCatch tryCatch;
	bool closed = false;
	if (BoolConverter::optArg(0, &closed, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Contour::ArcLength"));
		return;
	}

	double arcLength = cv::arcLength(FF_UNWRAP_CONTOUR_AND_GET(info.This()), closed);
	FF_RETURN(Nan::New(arcLength));
}

NAN_METHOD(Contour::BoundingRect) {
	FF_OBJ jsRect = FF::newInstance(Nan::New(Rect::constructor));
	FF_UNWRAP(jsRect, Rect)->rect = cv::boundingRect(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsRect);
}

NAN_METHOD(Contour::ConvexHull) {
	FF::TryCatch tryCatch;
	bool clockwise = false;
	if (BoolConverter::optArg(0, &clockwise, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Contour::ConvexHull"));
		return;
	}

	std::vector<cv::Point> hullPoints;
	cv::convexHull(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		hullPoints,
		clockwise,
		true
	);
	FF_OBJ jsHull = FF::newInstance(Nan::New(Contour::constructor));
	FF_UNWRAP_CONTOUR_AND_GET(jsHull) = hullPoints;
	FF_UNWRAP(jsHull, Contour)->hierarchy = cv::Vec4i(-1, -1, -1, -1);
	FF_RETURN(jsHull);
}

NAN_METHOD(Contour::ConvexHullIndices) {
	FF::TryCatch tryCatch;
	bool clockwise = false;
	if (BoolConverter::optArg(0, &clockwise, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Contour::ConvexHullIndices"));
		return;
	}

	std::vector<int> hullIndices;
	cv::convexHull(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		hullIndices,
		clockwise,
		false
	);
	FF_PACK_ARRAY(jsHullIndices, hullIndices);
	FF_RETURN(jsHullIndices);
}
NAN_METHOD(Contour::ConvexityDefects) {
	FF::TryCatch tryCatch;
	std::vector<int> hull;
	if (IntArrayConverter::arg(0, &hull, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Contour::ConvexityDefects"));
		return;
	}

	std::vector<cv::Vec4d> defects;
	cv::convexityDefects(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		hull,
		defects
	);

	info.GetReturnValue().Set(ObjectArrayConverter<Vec4, cv::Vec4d>::wrap(defects));
}

NAN_METHOD(Contour::MinEnclosingCircle) {
	cv::Point2f center;
	float radius;
	cv::minEnclosingCircle(FF_UNWRAP_CONTOUR_AND_GET(info.This()), center, radius);

	FF_OBJ jsCircle = FF_NEW_OBJ();
	FF_OBJ jsCenter = FF::newInstance(Nan::New(Point2::constructor));
	FF_UNWRAP_PT2_AND_GET(jsCenter) = center;
	Nan::Set(jsCircle, FF_NEW_STRING("center"), jsCenter);
	Nan::Set(jsCircle, FF_NEW_STRING("radius"), Nan::New((double)radius));
	FF_RETURN(jsCircle);
}

NAN_METHOD(Contour::MinEnclosingTriangle) {
	std::vector<cv::Point2f> triangle;
	cv::minEnclosingTriangle(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		triangle
	);
	info.GetReturnValue().Set(ObjectArrayConverter<Point2, cv::Point2d, cv::Point2f>::wrap(triangle));
}

NAN_METHOD(Contour::PointPolygonTest) {
	FF::TryCatch tryCatch;
	cv::Point2d point;
	if (Point2::Converter::arg(0, &point, info)) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Contour::PointPolygonTest"));
		return;
	}

	double dist = cv::pointPolygonTest(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		point,
		true
	);
	FF_RETURN(Nan::New(dist));
}

NAN_METHOD(Contour::MatchShapes) {
	FF::TryCatch tryCatch;
	std::vector<cv::Point> contour2;
	uint method;
	if (
		Contour::Converter::arg(0, &contour2, info) ||
		UintConverter::arg(1, &method, info)
	) {
		tryCatch.throwNew(tryCatch.formatCatchedError("Contour::MatchShapes"));
		return;
	}

	// parameter not supported
	double parameter = 0.0;
	double cmp = cv::matchShapes(
		FF_UNWRAP_CONTOUR_AND_GET(info.This()),
		contour2,
		(int)method,
		parameter
	);
	FF_RETURN(Nan::New(cmp));
}

NAN_METHOD(Contour::MinAreaRect) {
	FF_OBJ jsRotatedRect = FF::newInstance(Nan::New(RotatedRect::constructor));
	FF_UNWRAP_ROTATEDRECT_AND_GET(jsRotatedRect) = cv::minAreaRect(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsRotatedRect);
}

NAN_METHOD(Contour::FitEllipse) {
	FF_OBJ jsRotatedRect = FF::newInstance(Nan::New(RotatedRect::constructor));
	FF_UNWRAP_ROTATEDRECT_AND_GET(jsRotatedRect) = cv::fitEllipse(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsRotatedRect);
}

NAN_METHOD(Contour::_Moments) {
	FF_OBJ jsMoments = FF::newInstance(Nan::New(Moments::constructor));
	FF_UNWRAP(jsMoments, Moments)->moments = cv::moments(FF_UNWRAP_CONTOUR_AND_GET(info.This()));
	FF_RETURN(jsMoments);
}
