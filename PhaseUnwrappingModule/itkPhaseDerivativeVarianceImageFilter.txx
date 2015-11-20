/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkPhaseDerivativeVarianceImageFilter_txx
#define __itkPhaseDerivativeVarianceImageFilter_txx
 
namespace itk {

template< typename TInputImage, typename TOutputImage >
PhaseDerivativeVarianceImageFilter< TInputImage, TOutputImage >
::PhaseDerivativeVarianceImageFilter()
{

// m_Normalize = true;

}

template< typename TInputImage, typename TOutputImage >
void
PhaseDerivativeVarianceImageFilter< TInputImage, TOutputImage >
::GenerateData()
{

  // Get pointers to input and output images
  typename TInputImage::ConstPointer input = this->GetInput();
  
  typename TInputImage::Pointer output = TInputImage::New();
  output->SetRegions( input->GetLargestPossibleRegion() );
  output->Allocate();
  
  output->FillBuffer( 0 );
  typename TVectorImage::Pointer grad = this->ComposeVector();
  grad->Update();
  // Set up second set of iterators
  // Normal iterator for output
  // Neighborhood iterator for vector
  
  typename TInputImage::SizeType radius;
  radius.Fill( 1 );
  ItType outputIt( output, output->GetLargestPossibleRegion() );
  NVItType nGradIt( radius, grad, output->GetLargestPossibleRegion() );
	
  outputIt.GoToBegin();
  nGradIt.GoToBegin();
	
  while( !outputIt.IsAtEnd() ) {
		
    // by default, valarray is filled with zeros
    std::valarray< double > means((unsigned int)TInputImage::ImageDimension);

    for (unsigned int ii = 0; ii < TInputImage::ImageDimension; ++ii) {
			
      means[ii] = nGradIt.GetPrevious( ii )[ii];
      means[ii] += nGradIt.GetCenterPixel()[ii];
      means[ii] += nGradIt.GetNext( ii )[ii];
			
    }
		
    means /= (double) nGradIt.Size();
		
    // fill sums with default zero value
    std::valarray< double > sums((unsigned int)TInputImage::ImageDimension);
		
    // Squared differences from the mean
    for (unsigned int ii = 0; ii < TInputImage::ImageDimension; ++ii) {
		
      sums[ii] = pow(nGradIt.GetPrevious( ii )[ii] - means[ii], 2);
      sums[ii] += pow(nGradIt.GetCenterPixel()[ii] - means[ii], 2);
      sums[ii] += pow(nGradIt.GetNext( ii )[ii] - means[ii], 2);
	
    }
	
	// Check this one more time
    outputIt.Set( pow(sums, 0.5).sum() / pow(nGradIt.Size(), 2) );
    
    ++outputIt;
    ++nGradIt;
	
  }

  this->GraftOutput( output );
  this->AllocateOutputs();
  
}

template < typename TInputImage, typename TOutputImage > 
void 
PhaseDerivativeVarianceImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const 
{

  Superclass::PrintSelf(os,indent); 

}
 
}// end namespace itk
 
#endif
