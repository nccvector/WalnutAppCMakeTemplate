#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Render panel");
		ImGui::Text("Render time: %.3fms", mLastRenderTime);

		if(ImGui::Button("Render"))
			Render();

		ImGui::End();


		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		mViewportWidth = ImGui::GetContentRegionAvail().x;
		mViewportHeight = ImGui::GetContentRegionAvail().y;

		if(mImage)
			ImGui::Image(mImage->GetDescriptorSet(), { (float)mImage->GetWidth(), (float)mImage->GetHeight() });

		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}

	void Render()
	{
		Timer timer;

		if(!mImage || mViewportWidth != mImage->GetWidth() || mViewportHeight != mImage->GetHeight())
		{
			mImage = std::make_shared<Image>(mViewportWidth, mViewportHeight, ImageFormat::RGBA);
			delete[] mImageData;
			mImageData = new uint32_t[mViewportWidth * mViewportHeight];
		}

		for(uint32_t i = 0; i < mViewportWidth * mViewportHeight; i++)
			mImageData[i] = 0xffff00ff;
		
		mImage->SetData(mImageData);

		mLastRenderTime = timer.ElapsedMillis();
	}

private:
	std::shared_ptr<Image> mImage;
	uint32_t* mImageData = nullptr;
	uint32_t mViewportWidth = 0, mViewportHeight = 0;
	float mLastRenderTime = 0.0f;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}