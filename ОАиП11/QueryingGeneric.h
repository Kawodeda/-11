
#pragma once

#include <type_traits>

namespace qry
{
	template<typename TSource, typename TSelector>
	TSource& GetLastSatisfyingPredicate(TSource* source, size_t count, bool(*predicate) (TSelector, TSelector), TSelector(*selector) (TSource&))
	{
		size_t index = 0;
		for (size_t i = 1; i < count; ++i)
		{
			if (predicate(selector(source[i]), selector(source[index])))
			{
				index = i;
			}
		}

		return source[index];
	}


	template<typename TSource, typename TSelector>
	TSource& GetMax(TSource* source, size_t count, TSelector(*selector) (TSource&))
	{
		return GetLastSatisfyingPredicate<TSource, TSelector>(source, count, [](TSelector a, TSelector b) { return a > b; }, selector);
	}

	template<typename TSource, typename TSelector>
	TSource& GetMin(TSource* source, size_t count, TSelector(*selector) (TSource&))
	{
		return GetLastSatisfyingPredicate<TSource, TSelector>(source, count, [](TSelector a, TSelector b) { return a < b; }, selector);
	}

	template<typename TSource>
	bool TryFind(TSource* source, size_t count, bool (*match) (TSource&), TSource& result)
	{
		for (size_t i = 0; i < count; ++i)
		{
			if (match(source[i]))
			{
				result = source[i];
				return true;
			}
		}

		return false;
	}

	template<typename TSource, typename TResult, typename TSelector>
	TResult Aggregate(TSource* source, size_t count, void(*operation) (TResult&, TSelector), TSelector(*selector) (TSource&))
	{
		TResult result = TResult();
		for (size_t i = 0; i < count; ++i)
		{
			operation(result, selector(source[i]));
		}

		return result;
	}

	template<typename TSource, typename TResult = int>
	TResult Sum(TSource* source, size_t count, TResult(*selector) (TSource&))
	{
		static_assert(std::is_arithmetic_v<TResult>, "Result type must be arithmetic");

		return Aggregate<TSource, TResult, TResult>
			(source,
				count,
				[](TResult& sum, TResult term) { sum += term; },
				selector);
	}

} // namespace qry
