//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FirstUWPApp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	// pointer press/release handlers
	pressedTarget->PointerPressed += ref new PointerEventHandler(this, &MainPage::target_PointerPressed);
	pressedTarget->PointerReleased += ref new PointerEventHandler(this, &MainPage::target_PointerReleased);
}

// A PointerPressed event is sent whenever a mouse button, finger, or pen is pressed to make
// contact with an object
void MainPage::target_PointerPressed(Object^ sender, PointerRoutedEventArgs^ e)
{
	pressedTarget->Background = ref new SolidColorBrush(Windows::UI::Colors::RoyalBlue);
	pressedTargetText->Text = "Pointer Pressed";
}

// A PointerReleased event is sent whenever a mouse button, finger, or pen is released to remove
// contact from an object
void MainPage::target_PointerReleased(Object^ sender, PointerRoutedEventArgs^ e)
{
	pressedTarget->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
	pressedTargetText->Text = "Pointer Released";
}