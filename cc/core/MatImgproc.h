#include "Mat.h"
#include <opencv2/imgproc.hpp>

#ifndef __FF_MATIMGPROC_H__
#define __FF_MATIMGPROC_H__

class MatImgproc {
public:
  static void Init(v8::Local<v8::FunctionTemplate> ctor);

	struct BaseResizeWorker;
	struct RescaleWorker;
	static NAN_METHOD(Rescale);
	static NAN_METHOD(RescaleAsync);
	struct ResizeWorker;
  static NAN_METHOD(Resize);
	static NAN_METHOD(ResizeAsync);
	struct ResizeToMaxWorker;
  static NAN_METHOD(ResizeToMax);
	static NAN_METHOD(ResizeToMaxAsync);


	struct ThresholdWorker;
	static NAN_METHOD(Threshold);
	static NAN_METHOD(ThresholdAsync);

	struct AdaptiveThresholdWorker;
	static NAN_METHOD(AdaptiveThreshold);
	static NAN_METHOD(AdaptiveThresholdAsync);

	struct InRangeWorker;
	static NAN_METHOD(InRange);
	static NAN_METHOD(InRangeAsync);

	struct CvtColorWorker;
	static NAN_METHOD(CvtColor);
	static NAN_METHOD(CvtColorAsync);
	struct BgrToGrayWorker;
	static NAN_METHOD(BgrToGray);
	static NAN_METHOD(BgrToGrayAsync);

	struct WarpWorker;
	struct WarpAffineWorker;
	struct WarpPerspectiveWorker;
	static NAN_METHOD(WarpAffine);
	static NAN_METHOD(WarpAffineAsync);
	static NAN_METHOD(WarpPerspective);
	static NAN_METHOD(WarpPerspectiveAsync);

	struct MorphWorker;
	struct DilateWorker;
	struct ErodeWorker;
	struct MorphologyExWorker;
	static NAN_METHOD(Dilate);
	static NAN_METHOD(DilateAsync);
	static NAN_METHOD(Erode);
	static NAN_METHOD(ErodeAsync);
	static NAN_METHOD(MorphologyEx);
	static NAN_METHOD(MorphologyExAsync);

	struct DistanceTransformWorker;
	static NAN_METHOD(DistanceTransform);
	static NAN_METHOD(DistanceTransformAsync);
	struct DistanceTransformWithLabelsWorker;
	static NAN_METHOD(DistanceTransformWithLabels);
	static NAN_METHOD(DistanceTransformWithLabelsAsync);

	struct BlurWorker;
	static NAN_METHOD(Blur);
	static NAN_METHOD(BlurAsync);

	struct GaussianBlurWorker;
	static NAN_METHOD(GaussianBlur);
	static NAN_METHOD(GaussianBlurAsync);

	struct MedianBlurWorker;
	static NAN_METHOD(MedianBlur);
	static NAN_METHOD(MedianBlurAsync);

	struct ConnectedComponentsWorker;
	static NAN_METHOD(ConnectedComponents);
	static NAN_METHOD(ConnectedComponentsAsync);
	struct ConnectedComponentsWithStatsWorker;
	static NAN_METHOD(ConnectedComponentsWithStats);
	static NAN_METHOD(ConnectedComponentsWithStatsAsync);

	struct GrabCutWorker;
	static NAN_METHOD(GrabCut);
	static NAN_METHOD(GrabCutAsync);

	struct WatershedWorker;
	static NAN_METHOD(Watershed);
	static NAN_METHOD(WatershedAsync);

	struct MomentsWorker;
	static NAN_METHOD(_Moments);
	static NAN_METHOD(_MomentsAsync);

	struct FindContoursWorker;
	static NAN_METHOD(FindContours);
	static NAN_METHOD(FindContoursAsync);

	static NAN_METHOD(DrawContours);

	struct DrawWorker;
	struct DrawLineWorker;
	static NAN_METHOD(DrawLine);
	struct DrawArrowedLineWorker;
	static NAN_METHOD(DrawArrowedLine);
	struct DrawCircleWorker;
	static NAN_METHOD(DrawCircle);
	struct DrawRectangleWorker;
	static NAN_METHOD(DrawRectangle);
	struct DrawEllipseWorker;
	static NAN_METHOD(DrawEllipse);
	struct DrawPolylinesWorker;
	static NAN_METHOD(DrawPolylines);
	struct DrawFillPolyWorker;
	static NAN_METHOD(DrawFillPoly);
	struct DrawFillConvexPolyWorker;
	static NAN_METHOD(DrawFillConvexPoly);
	struct PutTextWorker;
	static NAN_METHOD(PutText);

	struct MatchTemplateWorker;
	static NAN_METHOD(MatchTemplate);
	static NAN_METHOD(MatchTemplateAsync);

	struct CannyWorker;
	static NAN_METHOD(Canny);
	static NAN_METHOD(CannyAsync);

	struct SobelScharrWorker;
	struct SobelWorker;
	struct ScharrWorker;
	static NAN_METHOD(Sobel);
	static NAN_METHOD(SobelAsync);
	static NAN_METHOD(Scharr);
	static NAN_METHOD(ScharrAsync);

	struct LaplacianWorker;
	static NAN_METHOD(Laplacian);
	static NAN_METHOD(LaplacianAsync);

	struct PyrWorker;
	static NAN_METHOD(PyrDown);
	static NAN_METHOD(PyrDownAsync);
	static NAN_METHOD(PyrUp);
	static NAN_METHOD(PyrUpAsync);

	struct BuildPyramidWorker;
	static NAN_METHOD(BuildPyramid);
	static NAN_METHOD(BuildPyramidAsync);

	struct HoughLinesWorker;
	static NAN_METHOD(HoughLines);
	static NAN_METHOD(HoughLinesAsync);

	struct HoughLinesPWorker;
	static NAN_METHOD(HoughLinesP);
	static NAN_METHOD(HoughLinesPAsync);

	struct HoughCirclesWorker;
	static NAN_METHOD(HoughCircles);
	static NAN_METHOD(HoughCirclesAsync);

	struct EqualizeHistWorker;
	static NAN_METHOD(EqualizeHist);
	static NAN_METHOD(EqualizeHistAsync);

	struct CompareHistWorker;
	static NAN_METHOD(CompareHist);
	static NAN_METHOD(CompareHistAsync);

	struct FloodFillWorker;
	static NAN_METHOD(FloodFill);
	static NAN_METHOD(FloodFillAsync);

	struct BilateralFilterWorker;
	static NAN_METHOD(BilateralFilter);
	static NAN_METHOD(BilateralFilterAsync);

	struct BoxFilterWorker;
	static NAN_METHOD(BoxFilter);
	static NAN_METHOD(BoxFilterAsync);
	struct SqrBoxFilterWorker;
	static NAN_METHOD(SqrBoxFilter);
	static NAN_METHOD(SqrBoxFilterAsync);

	struct Filter2DWorker;
	static NAN_METHOD(Filter2D);
	static NAN_METHOD(Filter2DAsync);

	struct SepFilter2DWorker;
	static NAN_METHOD(SepFilter2D);
	static NAN_METHOD(SepFilter2DAsync);

	struct CornerHarrisWorker;
	static NAN_METHOD(CornerHarris);
	static NAN_METHOD(CornerHarrisAsync);

	struct CornerSubPixWorker;
	static NAN_METHOD(CornerSubPix);
	static NAN_METHOD(CornerSubPixAsync);
	
	struct BaseCornerEigenValWorker;
	struct CornerMinEigenValWorker;
	static NAN_METHOD(CornerMinEigenVal);
	static NAN_METHOD(CornerMinEigenValAsync);
	struct CornerEigenValsAndVecsWorker;
	static NAN_METHOD(CornerEigenValsAndVecs);
	static NAN_METHOD(CornerEigenValsAndVecsAsync);
};

#endif