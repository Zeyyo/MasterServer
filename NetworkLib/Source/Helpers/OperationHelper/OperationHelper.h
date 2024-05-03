#pragma once

template<typename ExceptionT>
class OperationHelper {
public:
    template<typename OperationFuncT, typename HandleExceptionFuncT>
    bool static AttemptOperation(int maxAttempts, DWORD nTimeoutMilliseconds, OperationFuncT operation, HandleExceptionFuncT handleException) {
        for (int count = 0; count < maxAttempts; count++) {
            try {
                operation();
                return true;
            }
            catch (ExceptionT& eT) {
                handleException(eT);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(nTimeoutMilliseconds));
        }
        return false;
    }
};