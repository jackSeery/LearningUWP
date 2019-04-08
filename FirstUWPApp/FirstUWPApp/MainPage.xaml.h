//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <map>

namespace FirstUWPApp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void Pointer_Entered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Pointer_Pressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Pointer_Moved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Pointer_Released(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void Pointer_Wheel_Changed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);

		void CreateOrUpdatePropertyPopUp(Windows::UI::Input::PointerPoint^ currentPoint);
		Platform::String^ GetPointerProperties(Windows::UI::Input::PointerPoint^ currentPoint);
		Platform::String^ GetDeviceSpecificProperties(Windows::UI::Input::PointerPoint^ currentPoint);
		Platform::String^ GetMouseProperties(Windows::UI::Input::PointerPoint^ currentPoint);
		Platform::String^ GetTouchProperties(Windows::UI::Input::PointerPoint^ currentPoint);
		Platform::String^ GetPenProperties(Windows::UI::Input::PointerPoint^ currentPoint);

		void RenderPropertyPopUp(Platform::String^ pointerProperties, Platform::String^ deviceSpecificProperties, Windows::UI::Input::PointerPoint^ currentPoint);
		void HidePropertyPopUp(Windows::UI::Input::PointerPoint^ currentPoint);

		std::map<unsigned int, Windows::UI::Xaml::Controls::StackPanel^> popups;
	};
}
