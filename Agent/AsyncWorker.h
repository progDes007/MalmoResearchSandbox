#pragma once
#include "agent_global.h"


class AGENT_EXPORT AsyncWorker
{
	Q_DISABLE_COPY(AsyncWorker)
public:
	AsyncWorker(bool backgroundPriority = false);
	virtual ~AsyncWorker();

public:
	enum Status 
	{
		eNotStarted,
		eCancelling,
		eCancelled,
		eRunning,
		eReady,
	};

	struct Progress
	{
		int totalProgress;
		int currentStageProgress;
		std::wstring message; // Localized message to be displayed in UI.
	};
		
	/// starts async work
	void startAsync();
		
	/// returns current progress of async work
	virtual Progress progress() const; 

	/// wait until work is finished 
	void join();
		
	/// cancel current work in progress
	/// Thread-safe.
	virtual void cancel();
		
	/// current work status
	///	eNotStarted	-	work not started yet
	///	eWorking	-	work in progress
	///	eCancelling	-	work cancel in progress
	///	eCancelled	-	work is canceled
	///	eFinished	-	work is finished
	///	eError		-	error occured during work, work is not finished
	Status status() const;

protected:
	/// implementation of job done by worker in async 
	virtual void  doJob() = 0;
	/// setts current progress
	void setProgress(int totalProgress, int currentStageProgress, const std::wstring& message);
	/// is job cancelled
	bool isCancelled() const;
	/// waits for job and throws any exceptions from job
	void pullException();
	/// Is feature valid (future refers to a shared state, to check if get() was called)
	bool isValid() const;
private:
	class Impl;
	std::unique_ptr<Impl> m_impl;

};
