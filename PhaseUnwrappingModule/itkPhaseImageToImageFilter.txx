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
#ifndef __itkPhaseImageToImageFilter_txx
#define __itkPhaseImageToImageFilter_txx
 
namespace itk {

template< class TInputImage, class TOutputImage >
typename TInputImage::PixelType
PhaseImageToImageFilter< TInputImage, TOutputImage >
::Wrap( typename TInputImage::PixelType pixel )
{

  WrapFunctorType wrap;
  return wrap(pixel);

}

template< class TInputImage, class TOutputImage >
typename TInputImage::PixelType
PhaseImageToImageFilter< TInputImage, TOutputImage >
::Unwrap( typename TInputImage::PixelType target,
          typename TInputImage::PixelType relativeToReference )
{
  
  return relativeToReference += this->Wrap(target - relativeToReference);
  
}

template < typename TInputImage, typename TOutputImage > 
void 
PhaseImageToImageFilter< TInputImage, TOutputImage >
::PrintSelf( std::ostream& os, Indent indent ) const 
{

  Superclass::PrintSelf(os,indent); 

  os << indent << "No parameters." << std::endl;
  
}


}// end namespace itk
 
#endif // __itkPhaseImageToImageFilter_txx
