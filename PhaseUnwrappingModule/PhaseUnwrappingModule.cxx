#include "itkImageFileWriter.h"
#include "itkPluginUtilities.h"
#include "itkCastImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

#include "itkQualityGuidedPhaseUnwrappingImageFilter.h"

#include "PhaseUnwrappingModuleCLP.h"

namespace
{

template <class T>
int DoIt( int argc, char * argv[], T )
{
  PARSE_ARGS;

  typedef    T InputPixelType;
  //typedef    T OutputPixelType;

  typedef itk::Image<InputPixelType,  3> InputImageType;
  typedef itk::Image<double, 3> PhaseImageType;
  //typedef itk::Image<OutputPixelType, 3> OutputImageType;
  typedef itk::Image<double, 3> OutputImageType;

  typedef itk::ImageFileReader<InputImageType>  ReaderType;
  typedef itk::ImageFileWriter<OutputImageType> WriterType;

  typedef itk::CastImageFilter<InputImageType, PhaseImageType>  InputCastFilterType;
  typedef itk::RescaleIntensityImageFilter<PhaseImageType, PhaseImageType> RescaleFilterType;
  typedef itk::QualityGuidedPhaseUnwrappingImageFilter< PhaseImageType, OutputImageType > QGFilterType;
  
  typename ReaderType::Pointer reader = ReaderType::New();

  reader->SetFileName( inputVolume.c_str() );

  typename InputCastFilterType::Pointer castFilter = InputCastFilterType::New();
  castFilter->SetInput( reader->GetOutput() );
  
  typename RescaleFilterType::Pointer rescaleFilter = RescaleFilterType::New();
  rescaleFilter->SetOutputMinimum(0.0);
  rescaleFilter->SetOutputMaximum(vnl_math::pi * 2);
  rescaleFilter->SetInput( castFilter->GetOutput() );

  typename WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( outputVolume.c_str() );

  typename QGFilterType::Pointer qgFilter = QGFilterType::New();
  qgFilter->SetInput( rescaleFilter->GetOutput() );
  
  // Convert the specified true phase point from RAS coordinates to image index
  typename InputImageType::IndexType truePhaseIndex;
  if( truePhase.size() > 0 )
    {
    typename InputImageType::PointType lpsPoint;
    // RAS to LPS
    lpsPoint[0] = -truePhase[0][0];
    lpsPoint[1] = -truePhase[0][1];
    lpsPoint[2] = truePhase[0][2];
    reader->GetOutput()->TransformPhysicalPointToIndex(lpsPoint, truePhaseIndex);
    }
  else
    {
    std::cerr << "No truePhase point specified. Image center is used instead." << std::endl;
    truePhaseIndex[0] = reader->GetOutput()->GetLargestPossibleRegion().GetSize()[0] / 2;
    truePhaseIndex[1] = reader->GetOutput()->GetLargestPossibleRegion().GetSize()[1] / 2;
    }
  qgFilter->SetTruePhase( truePhaseIndex );
  writer->SetInput( qgFilter->GetOutput() );
  writer->SetUseCompression(1);
  writer->Update();

  return EXIT_SUCCESS;
}

} // end of anonymous namespace

int main( int argc, char * argv[] )
{
  PARSE_ARGS;

  itk::ImageIOBase::IOPixelType     pixelType;
  itk::ImageIOBase::IOComponentType componentType;

  try
    {
    itk::GetImageType(inputVolume, pixelType, componentType);

    // This filter handles all types on input, but only produces
    // signed types
    switch( componentType )
      {
      case itk::ImageIOBase::UCHAR:
        return DoIt( argc, argv, static_cast<unsigned char>(0) );
        break;
      case itk::ImageIOBase::CHAR:
        return DoIt( argc, argv, static_cast<char>(0) );
        break;
      case itk::ImageIOBase::USHORT:
        return DoIt( argc, argv, static_cast<unsigned short>(0) );
        break;
      case itk::ImageIOBase::SHORT:
        return DoIt( argc, argv, static_cast<short>(0) );
        break;
      case itk::ImageIOBase::UINT:
        return DoIt( argc, argv, static_cast<unsigned int>(0) );
        break;
      case itk::ImageIOBase::INT:
        return DoIt( argc, argv, static_cast<int>(0) );
        break;
      case itk::ImageIOBase::ULONG:
        return DoIt( argc, argv, static_cast<unsigned long>(0) );
        break;
      case itk::ImageIOBase::LONG:
        return DoIt( argc, argv, static_cast<long>(0) );
        break;
      case itk::ImageIOBase::FLOAT:
        return DoIt( argc, argv, static_cast<float>(0) );
        break;
      case itk::ImageIOBase::DOUBLE:
        return DoIt( argc, argv, static_cast<double>(0) );
        break;
      case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
      default:
        std::cout << "unknown component type" << std::endl;
        break;
      }
    }

  catch( itk::ExceptionObject & excep )
    {
    std::cerr << argv[0] << ": exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}
