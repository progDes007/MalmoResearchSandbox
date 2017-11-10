#include "stdafx.h"
#include "AsyncWorker.h"
#include <future>
#include <atomic>


class AsyncWorker::Impl 
{
public:

	AsyncWorker* self;
	bool m_backgroundThreadPriority;
	std::future<void> m_buildFuture;
	std::atomic<bool> m_bCancel;
	std::shared_ptr<AsyncWorker::Progress> m_progress;

	void jobWrapper();
};
	
void AsyncWorker::Impl::jobWrapper()
{

	self->doJob();

}


//////////////////////////////////////
AsyncWorker::AsyncWorker(bool backgroundPriority)
	:m_impl(new Impl)
{
	m_impl->m_bCancel = false;
	m_impl->self = this;
	m_impl->m_backgroundThreadPriority = backgroundPriority;
}

AsyncWorker::~AsyncWorker()
{
	cancel();
	join();
}

void AsyncWorker::setProgress(int totalProgress, int currentStageProgress, const std::wstring& message)
{
	std::shared_ptr<AsyncWorker::Progress> newProgress(new AsyncWorker::Progress);

	newProgress->message = message;
	newProgress->currentStageProgress = currentStageProgress;
	newProgress->totalProgress = totalProgress;

	std::atomic_store(&m_impl->m_progress, newProgress);
}

AsyncWorker::Progress AsyncWorker::progress() const
{
	if(auto progressPtr = std::atomic_load(&m_impl->m_progress))
	{
		Progress progress;
		progress.totalProgress = progressPtr->totalProgress;
		progress.currentStageProgress = progressPtr->currentStageProgress;
		progress.message = progressPtr->message;

		return progress;
	}
	else
	{
		Progress p;
		p.currentStageProgress = 0;
		p.totalProgress = 0;

		return p;
	}
}

AsyncWorker::Status AsyncWorker::status() const
{
	Status jobStatus;

	if (m_impl->m_buildFuture.valid())
	{
		auto result = m_impl->m_buildFuture.wait_for(std::chrono::seconds(0));
		if (m_impl->m_bCancel)
			jobStatus = (result == std::future_status::ready) ? eCancelled : eCancelling;
		else
			jobStatus = (result == std::future_status::ready) ? eReady : eRunning;
	}
	else
	{
		jobStatus = eNotStarted;
	}

	return jobStatus;
}

void AsyncWorker::join()
{
	if(m_impl->m_buildFuture.valid())
	{
		m_impl->m_buildFuture.wait();
	}
}

void AsyncWorker::cancel()
{
	m_impl->m_bCancel = true;
}

bool AsyncWorker::isCancelled() const
{
	return m_impl->m_bCancel.load();
}

void AsyncWorker::startAsync()
{
	assert(!m_impl->m_buildFuture.valid());
	m_impl->m_bCancel = false;
	m_impl->m_buildFuture = std::async(std::launch::async, &AsyncWorker::Impl::jobWrapper, m_impl.get());
}

void AsyncWorker::pullException()
{
	m_impl->m_buildFuture.get();
}

bool AsyncWorker::isValid() const
{
	return m_impl->m_buildFuture.valid();
}
